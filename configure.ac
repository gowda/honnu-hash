AC_INIT([honnu-hash],[0.5],[honnu-hash@gmail.com])

AM_INIT_AUTOMAKE

AM_CONFIG_HEADER([config.h])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_PROG_CC

AC_CHECK_TOOL([LD],[ld])

AC_CHECK_LIB([pthread], [pthread_mutex_init], , AC_MSG_ERROR([Posix threads \
                        library is required]))

AC_OUTPUT
