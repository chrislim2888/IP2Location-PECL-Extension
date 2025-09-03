/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Guruswamy Basavaiah                                          |
  +----------------------------------------------------------------------+
  Please contact support@ip2location.com  with any comments
*/
#ifndef PHP_IP2LOCATION_H
#define PHP_IP2LOCATION_H

/* The IP2Location.h checks for this but it's defined by config.w32 */
#if defined(PHP_WIN32) && defined(HAVE_IP2LOCATION_H)
#undef HAVE_IP2LOCATION_H
#endif

#include <IP2Location.h>
#include <php.h>

#define PHP_IP2LOCATION_EXTNAME "ip2location"
#define PHP_IP2LOCATION_VERSION "8.3.0"

PHP_MINIT_FUNCTION(ip2location);
PHP_MSHUTDOWN_FUNCTION(ip2location);
PHP_MINFO_FUNCTION(ip2location);

extern zend_module_entry ip2location_module_entry;
#define phpext_ip2location_ptr &ip2location_module_entry

ZEND_BEGIN_MODULE_GLOBALS(ip2location)
        IP2Location *ip2location_ptr;
ZEND_END_MODULE_GLOBALS(ip2location)

#ifdef ZTS
#define IP2LOCATION_G(v) TSRMG(ip2location_globals_id, zend_ip2location_globals *, v)
#else
#define IP2LOCATION_G(v) (ip2location_globals.v)
#endif


#endif
