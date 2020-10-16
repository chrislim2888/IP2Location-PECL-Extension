dnl config.m4 for extension ip2location 

dnl Base file contributed by Guruswamy Basavaiah

PHP_ARG_WITH(ip2location, for ip2location support,
dnl Make sure that the comment is aligned:
[  --with-ip2location             Include ip2location support])

if test "$PHP_IP2LOCATION" != "no"; then

  # --with-ip2location -> check with-path
  SEARCH_PATH="/usr/local /usr /opt/local"
  SEARCH_FOR="/include/IP2Location.h"
  AC_MSG_CHECKING([for ip2location files in default path])
  if test -r $PHP_IP2LOCATION/$SEARCH_FOR; then
    IP2LOCATION_DIR=$PHP_IP2LOCATION
  else # search default path list
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        IP2LOCATION_DIR=$i
      fi
    done
  fi

  if test -z "$IP2LOCATION_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the ip2location C library])
  else
    AC_MSG_RESULT([found in $IP2LOCATION_DIR])
  fi

  # --with-ip2location -> add include path
  PHP_ADD_INCLUDE($IP2LOCATION_DIR/include)

  # odd PHP4 fix
  if test "x$PHP_LIBDIR" = "x"; then
    PHP_LIBDIR=lib
  fi 

  # --with-ip2location -> check for lib and symbol presence
  LIBNAME=IP2Location # you may want to change this
  LIBSYMBOLOLD=IP2Location_open_mem
  LIBSYMBOLNEW=IP2Location_set_lookup_mode

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOLNEW,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $IP2LOCATION_DIR/$PHP_LIBDIR, IP2LOCATION_SHARED_LIBADD)
    AC_DEFINE(HAVE_IPLOCATIONLIB,1,[ ])
  ],[
    PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOLOLD,
    [
      PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $IP2LOCATION_DIR/$PHP_LIBDIR, IP2LOCATION_SHARED_LIBADD)
      AC_DEFINE(HAVE_IPLOCATIONLIB,1,[ ])
    ],[
      AC_MSG_ERROR([wrong ip2location, lib version >= 6.x.x is required or library not found])
    ],[
      -L$IP2LOCATION_DIR/$PHP_LIBDIR
    ])
  ],[
    -L$IP2LOCATION_DIR/$PHP_LIBDIR
  ])

  PHP_SUBST(IP2LOCATION_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ip2location, ip2location.c, $ext_shared)
fi

