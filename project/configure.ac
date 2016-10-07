AC_PREREQ(2.61)
AC_INIT([Common API C++ Tests],
        [1.0],
        [],
        [commonapi-tests])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([build-aux/config.h])
AC_CONFIG_FILES([Makefile])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([foreign 1.11 subdir-objects -Wall -Werror])
AM_MAINTAINER_MODE

AC_PROG_CXX
AC_LANG([C++])

LT_PREREQ(2.2)
LT_INIT

PKG_CHECK_MODULES(COMMON_API, [CommonAPI >= 0.7])
PKG_CHECK_MODULES(COMMON_API_DBUS, [CommonAPI-DBus])

AC_MSG_RESULT([
        $PACKAGE_NAME v$VERSION

		COMMONAPI_CFLAGS:  ${COMMONAPI_CFLAGS}
		COMMONAPI_LIBS:    ${COMMONAPI_LIBS}

        prefix:             ${prefix}
        CXXFLAGS:           ${CXXFLAGS}
        LDFLAGS:            ${LDFLAGS}
])

AC_OUTPUT

