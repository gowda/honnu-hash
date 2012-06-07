dnl Copyright (c) 2011 Basavanagowda Kanur <basavanagowda (at) gmail (dot) com>
dnl This file is part of honnu-hash.

dnl honnu-hash is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published
dnl by the Free Software Foundation; either version 3 of the License,
dnl or (at your option) any later version.

dnl honnu-hash is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see
dnl <http://www.gnu.org/licenses/>.


AC_INIT([honnu-hash],[0.5],[basavanagowda@gmail.com])

AM_INIT_AUTOMAKE

AM_CONFIG_HEADER([config.h])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 lib/Makefile])

AC_PROG_CC
AC_PROG_LIBTOOL

AC_CHECK_TOOL([LD],[ld])

AC_CHECK_LIB([pthread], [pthread_mutex_init], , AC_MSG_ERROR([Posix threads \
                        library is required]))

AC_OUTPUT
