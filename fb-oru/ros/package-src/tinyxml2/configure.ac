#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

##-------------------------------------------------------------------------
## Init
##-------------------------------------------------------------------------
AC_PREREQ([2.63])
AC_INIT([tinyxml2], [1.0])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
LT_INIT
AS_CASE([$host_alias],

	# Power PC build
	[powerpc*], [
	],

	# Local build (default)
	[
	  	# Force static linking to use the locally created GCC
	  	# This ensures we end up with an executable rather than a libtool
	  	# bash shell
	  	AC_DISABLE_SHARED
	]
)
AM_PROG_LIBTOOL

##LT_INIT
AM_SILENT_RULES

##-------------------------------------------------------------------------
## Local Data
##-------------------------------------------------------------------------
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/tinyxml2.cpp])
AC_CONFIG_HEADERS([config.h])

##-------------------------------------------------------------------------
## ENVIRONMENT
##-------------------------------------------------------------------------

# Set default options
CXXFLAGS="-Wall -Werror -fmessage-length=0 -std=gnu++11"

AS_CASE([$host_alias],

	# Power PC build
	[powerpc*], [
	],

	# Local build (default)
	[
		AC_SUBST([HOST_CPPFLAGS])
		AC_SUBST([HOST_LDFLAGS])
	]
)


##-------------------------------------------------------------------------
## BUILD VARS
##-------------------------------------------------------------------------

CXXFLAGS="$CXXFLAGS -O2 -g"


##-------------------------------------------------------------------------
## C++
##-------------------------------------------------------------------------
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX

# Check for C++ compiler
AS_CASE([$host_alias],
  [powerpc*], [AS_IF( [test "x$CXX" == xg++], [AC_MSG_ERROR([No Powerpc compiler found])] )],
  [
  ]
)

##-------------------------------------------------------------------------
## Checks for libraries.
##-------------------------------------------------------------------------


##-------------------------------------------------------------------------
## Checks for functions.
##-------------------------------------------------------------------------


##-------------------------------------------------------------------------
## Created files
##-------------------------------------------------------------------------
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

echo "
$PACKAGE_NAME version $PACKAGE_VERSION
HOST...........: $host_alias
Prefix.........: $prefix
C++ Compiler...: $CXX $CXXFLAGS $CPPFLAGS
Linker.........: $LD $LDFLAGS $LIBS
"
