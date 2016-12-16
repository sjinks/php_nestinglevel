#ifndef PHP_NL_H
#define PHP_NL_H

#include <main/php.h>

#define PHP_NL_EXTNAME  "nestinglimit"
#define PHP_NL_EXTVER   "0.1"

#ifdef ZTS
#	include "TSRM.h"
#	define NL_G(v) TSRMG(nl_globals_id, zend_nl_globals*, v)
#else
#	define NL_G(v) (nl_globals.v)
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
#	define NL_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
#else
#	define NL_VISIBILITY_HIDDEN
#endif

ZEND_BEGIN_MODULE_GLOBALS(nl)
	long int current_level;
	long int maximum_level;
ZEND_END_MODULE_GLOBALS(nl)

NL_VISIBILITY_HIDDEN extern ZEND_DECLARE_MODULE_GLOBALS(nl);

#ifdef COMPILE_DL_NL
NL_VISIBILITY_HIDDEN
#endif
extern zend_module_entry nl_module_entry;

#define phpext_nl_ptr &nl_module_entry

#endif /* PHP_NL_H */
