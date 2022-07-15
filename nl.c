#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_nl.h"
#include <Zend/zend.h>
#include <Zend/zend_execute.h>
#include <ext/standard/info.h>

#if PHP_VERSION_ID >= 70000
static void (*old_execute_ex)(zend_execute_data*);
static void (*old_execute_internal)(zend_execute_data*, zval*);
#else
static void (*old_execute_ex)(zend_execute_data* TSRMLS_DC);
static void (*old_execute_internal)(zend_execute_data*, zend_fcall_info*, int TSRMLS_DC);
#endif

ZEND_DECLARE_MODULE_GLOBALS(nl);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("nl.max_level", "0", PHP_INI_ALL, OnUpdateLong, maximum_level, zend_nl_globals, nl_globals)
PHP_INI_END()

static void nl_execute_ex(
	zend_execute_data* execute_data
#if PHP_VERSION_ID < 70000
	TSRMLS_DC
#endif
)
{
	long int current = ++NL_G(current_level);
	long int maximum = NL_G(maximum_level);

	if (maximum > 0 && current > maximum) {
		zend_error(E_ERROR, "Maximum function nesting level of '%ld' has been reached", maximum);
	}

#if PHP_VERSION_ID >= 70000
	old_execute_ex(execute_data);
#else
	old_execute_ex(execute_data TSRMLS_CC);
#endif

	--NL_G(current_level);
}

static void nl_execute_internal(
#if PHP_VERSION_ID >= 70000
	zend_execute_data* execute_data, zval* return_value
#else
	zend_execute_data* execute_data_ptr, zend_fcall_info* fci, int return_value_used TSRMLS_DC
#endif
)
{
	long int current = ++NL_G(current_level);
	long int maximum = NL_G(maximum_level);

	if (maximum > 0 && current > maximum) {
		zend_error(E_ERROR, "Maximum function nesting level of '%ld' has been reached", maximum);
	}

#if PHP_VERSION_ID >= 70000
	old_execute_internal(execute_data, return_value);
#else
	old_execute_internal(execute_data_ptr, fci, return_value_used TSRMLS_CC);
#endif

	--NL_G(current_level);
}

static PHP_MINIT_FUNCTION(nl)
{
	old_execute_ex        = zend_execute_ex;
	zend_execute_ex       = nl_execute_ex;
	old_execute_internal  = zend_execute_internal ? zend_execute_internal : &execute_internal;
	zend_execute_internal = nl_execute_internal;

	REGISTER_INI_ENTRIES();
	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(nl)
{
	zend_execute_ex       = old_execute_ex;
	zend_execute_internal = (old_execute_internal == &execute_internal) ? NULL : old_execute_internal;

	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(nl)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Function Nesting Limit", "enabled");
	php_info_print_table_row(2, "Version", PHP_NL_EXTVER);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(nl)
{
	nl_globals->current_level = -1;
	nl_globals->maximum_level =  0;
}

zend_module_entry nl_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_NL_EXTNAME,
	NULL,
	PHP_MINIT(nl),
	PHP_MSHUTDOWN(nl),
	NULL,
	NULL,
	PHP_MINFO(nl),
	PHP_NL_EXTVER,
	PHP_MODULE_GLOBALS(nl),
	PHP_GINIT(nl),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_NL
ZEND_GET_MODULE(nl)
#endif
