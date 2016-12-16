PHP_ARG_ENABLE(nestinglimit, whether to enable nesting limit extension, [ --enable-nestlimit  Enable nesting limit])

if test "$PHP_NESTINGLIMIT" = "yes"; then
	AC_DEFINE([HAVE_NESTINGLIMIT], [1], [Whether Nesting Limit is enabled])
	PHP_NEW_EXTENSION([nl], [nl.c], $ext_shared)
fi
