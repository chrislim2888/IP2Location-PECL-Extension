/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include "php_ip2location.h"

#if PHP_MAJOR_VERSION >= 8
#include "ip2location_arginfo.h"
#else
#include "ip2location_legacy_arginfo.h"
#endif

/* For PHP 8 */
#ifndef TSRMLS_CC
#define TSRMLS_CC
#endif

ZEND_DECLARE_MODULE_GLOBALS(ip2location)

#define IP2LOCATION_RECORD 0

/* the following code creates an entry for the module and registers it with Zend.*/
zend_module_entry ip2location_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_IP2LOCATION_EXTNAME,
	ext_functions,
	PHP_MINIT(ip2location),
	PHP_MSHUTDOWN(ip2location),
	NULL, 
	NULL, 
	PHP_MINFO(ip2location), 
	PHP_IP2LOCATION_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_IP2LOCATION
ZEND_GET_MODULE(ip2location)
#endif

	/* {{{ php_ip2location_init_globals
	 *  */ 
static void php_ip2location_init_globals(zend_ip2location_globals *ip2location_globals)
{
	ip2location_globals->ip2location_ptr = NULL;
}
/* }}} */

#define PHP_IP2LOCATION_DB_CHECK \
	if( IP2LOCATION_G(ip2location_ptr) == NULL ) { \
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "open db file with ip2location_open() before using this function"); \
		RETURN_FALSE; \
	}

/* {{{ PHP_MINIT_FUNCTION
 *  */
PHP_MINIT_FUNCTION(ip2location)
{
	ZEND_INIT_MODULE_GLOBALS(ip2location, php_ip2location_init_globals, NULL);

	/* For memory access type constants */
	REGISTER_LONG_CONSTANT("IP2LOCATION_FILE_IO", IP2LOCATION_FILE_IO, CONST_CS | CONST_PERSISTENT); 
	REGISTER_LONG_CONSTANT("IP2LOCATION_CACHE_MEMORY", IP2LOCATION_CACHE_MEMORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("IP2LOCATION_SHARED_MEMORY", IP2LOCATION_SHARED_MEMORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("IP2LOCATION_RECORD", IP2LOCATION_RECORD, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 *  */
PHP_MSHUTDOWN_FUNCTION(ip2location)
{
#if API_VERSION_NUMERIC >= 80100
	IP2Location_clear_memory();
#else
	IP2Location_delete_shm();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 *  */
PHP_MINFO_FUNCTION(ip2location)
{
	char buf[32];
	unsigned long ver;

	php_info_print_table_start();
	php_info_print_table_header(2, "ip2location support", "enabled");
	php_info_print_table_row(2, "extension version", PHP_IP2LOCATION_VERSION);
#if API_VERSION_NUMERIC >= 80100
	ver = IP2Location_api_version_number();
#else
	ver = IP2Location_api_version_num();
#endif
	snprintf(buf, sizeof(buf), "%d.%d.%d", API_VERSION_MAJOR, API_VERSION_MINOR, API_VERSION_RELEASE);
	if (API_VERSION_NUMERIC == ver) {
		php_info_print_table_row(2, "library version", buf);
	} else {
		/* display both headers/runtime versions when differ */
		php_info_print_table_row(2, "library headers version", buf);
		snprintf(buf, sizeof(buf), "%lu.%lu.%lu", ver / 10000, (ver / 100) % 100, ver % 100);
		php_info_print_table_row(2, "library runtime version", buf);
	}
	php_info_print_table_end();
}
/* }}} */


/* {{{ ip2location_open("db_filepath")
 * Returns the success or failure */
PHP_FUNCTION(ip2location_open)
{
	char * file_path = NULL;
	size_t path_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file_path, &path_len) == FAILURE) { 
		return;
	}
	if (IP2LOCATION_G(ip2location_ptr)) {
		IP2Location_close(IP2LOCATION_G(ip2location_ptr));
	}
	IP2LOCATION_G(ip2location_ptr) = IP2Location_open(file_path);
	if (IP2LOCATION_G(ip2location_ptr)) {
		RETURN_TRUE; 
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ ip2location_open_mem(method)
 * Returns the success or failure */
PHP_FUNCTION(ip2location_open_mem)
{
	long method;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &method) == FAILURE) { 
		return;
	}
	/*Shared memory method is not supported*/
	if( method == IP2LOCATION_FILE_IO || method == IP2LOCATION_CACHE_MEMORY || method == IP2LOCATION_SHARED_MEMORY ){
#if API_VERSION_NUMERIC >= 80100
		if(IP2Location_set_lookup_mode(IP2LOCATION_G(ip2location_ptr), method) == -1){
#else
		if(IP2Location_open_mem(IP2LOCATION_G(ip2location_ptr), method) == -1){
#endif
			RETURN_FALSE;
		}
		else{
			RETURN_TRUE;
		}
	}
	else{
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ ip2location_get_country_short("ip_address")
 * Returns ip address's country in short */
PHP_FUNCTION(ip2location_get_country_short)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) { 
		return;
	}
	record = IP2Location_get_country_short(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->country_short);
#else
	RETVAL_STRING(record->country_short, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_country_long("ip_address") 
 * Returns ip address's country in long */
PHP_FUNCTION(ip2location_get_country_long)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) { 
		return;
	}
	record = IP2Location_get_country_long(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->country_long);
#else
	RETVAL_STRING(record->country_long, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_region("ip_address") 
 * Returns ip address's region*/
PHP_FUNCTION(ip2location_get_region)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) { 
		return;
	}
	record = IP2Location_get_region(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->region);
#else
	RETVAL_STRING(record->region, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_city("ip_address") 
 * Returns ip address's city*/
PHP_FUNCTION(ip2location_get_city)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_city(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->city);
#else
	RETVAL_STRING(record->city, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_("ip_address") 
 * Returns ip address's isp information */
PHP_FUNCTION(ip2location_get_isp)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_isp(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->isp);
#else
	RETVAL_STRING(record->isp, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_latitude("ip_address") 
 * Returns ip address's latitude */
PHP_FUNCTION(ip2location_get_latitude)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_latitude(IP2LOCATION_G(ip2location_ptr), ip_address);
	RETVAL_DOUBLE(record->latitude);
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_longitude("ip_address") 
 * Returns ip address's longitude  information */
PHP_FUNCTION(ip2location_get_longitude)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_longitude(IP2LOCATION_G(ip2location_ptr), ip_address);
	RETVAL_DOUBLE(record->longitude);
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_domain("ip_address") 
 * Returns ip address's domain information */
PHP_FUNCTION(ip2location_get_domain)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_domain(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->domain);
#else
	RETVAL_STRING(record->domain, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_zipcode("ip_address") 
 * Returns ip address's zipcode information */
PHP_FUNCTION(ip2location_get_zipcode)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_zipcode(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->zip_code;
#else
	ret = record->zipcode;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_timezone("ip_address") 
 * Returns ip address's timezone information */
PHP_FUNCTION(ip2location_get_timezone)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_timezone(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->time_zone;
#else
	ret = record->timezone;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */


#if API_VERSION_NUMERIC == 80100
/* see https://github.com/chrislim2888/IP2Location-C-Library/issues/37 */
IP2LocationRecord *IP2Location_get_netspeed(IP2Location *handler, char *ip);
#endif

/* {{{ ip2location_get_netspeed("ip_address") 
 * Returns ip address's netspeed information */
PHP_FUNCTION(ip2location_get_netspeed)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}

	record = IP2Location_get_netspeed(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->net_speed;
#else
	ret = record->netspeed;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_iddcode("ip_address") 
 * Returns ip address's iddcode information */
PHP_FUNCTION(ip2location_get_iddcode)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_iddcode(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->idd_code;
#else
	ret = record->iddcode;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_areacode("ip_address") 
 * Returns ip address's areacode  information */
PHP_FUNCTION(ip2location_get_areacode)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_areacode(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->area_code;
#else
	ret = record->areacode;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_weatherstationcode("ip_address") 
 * Returns ip address's weatherstationcode information */
PHP_FUNCTION(ip2location_get_weatherstationcode)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_weatherstationcode(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->weather_station_code;
#else
	ret = record->weatherstationcode;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_weatherstationname("ip_address") 
 * Returns ip address's weatherstationname information */
PHP_FUNCTION(ip2location_get_weatherstationname)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_weatherstationname(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->weather_station_name;
#else
	ret = record->weatherstationname;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_mcc("ip_address") 
 * Returns ip address's mcc information */
PHP_FUNCTION(ip2location_get_mcc)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_mcc(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->mcc);
#else
	RETVAL_STRING(record->mcc, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_mnc("ip_address") 
 * Returns ip address's mnc information */
PHP_FUNCTION(ip2location_get_mnc)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_mnc(IP2LOCATION_G(ip2location_ptr), ip_address);
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(record->mnc);
#else
	RETVAL_STRING(record->mnc, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_mobilebrand("ip_address") 
 * Returns ip address's mobilebrand information */
PHP_FUNCTION(ip2location_get_mobilebrand)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_mobilebrand(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->mobile_brand;
#else
	ret = record->mobilebrand;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_elevation("ip_address") 
 * Returns ip address's elevation  information */
PHP_FUNCTION(ip2location_get_elevation)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_elevation(IP2LOCATION_G(ip2location_ptr), ip_address);
	RETVAL_DOUBLE(record->elevation);
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_usagetype("ip_address")
 * Returns ip address's internet connection usagetype information */
PHP_FUNCTION(ip2location_get_usagetype)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_usagetype(IP2LOCATION_G(ip2location_ptr), ip_address);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	ret = record->usage_type;
#else
	ret = record->usagetype;
#endif
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

#if API_VERSION_NUMERIC >= 80400
/* {{{ ip2location_get_addresstype("ip_address")
 * Returns ip address's internet connection address type information */
PHP_FUNCTION(ip2location_get_addresstype)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_addresstype(IP2LOCATION_G(ip2location_ptr), ip_address);
	ret = record->address_type;
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_category("ip_address")
 * Returns ip address's internet connection category information */
PHP_FUNCTION(ip2location_get_category)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_category(IP2LOCATION_G(ip2location_ptr), ip_address);
	ret = record->category;
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */
#endif

#if API_VERSION_NUMERIC >= 80600
/* {{{ ip2location_get_district("ip_address")
 * Returns ip address's internet connection district type information */
PHP_FUNCTION(ip2location_get_district)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_district(IP2LOCATION_G(ip2location_ptr), ip_address);
	ret = record->district;
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_asn("ip_address")
 * Returns ip address's internet connection as number information */
PHP_FUNCTION(ip2location_get_asn)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_asn(IP2LOCATION_G(ip2location_ptr), ip_address);
	ret = record->asn;
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */

/* {{{ ip2location_get_as("ip_address")
 * Returns ip address's internet connection as name information */
PHP_FUNCTION(ip2location_get_as)
{
	char *ip_address, *ret;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_as(IP2LOCATION_G(ip2location_ptr), ip_address);
	ret = record->as;
#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(ret);
#else
	RETVAL_STRING(ret, 1);
#endif
	IP2Location_free_record(record);
}
/* }}} */
#endif

/* {{{ ip2location_get_all("ip_address")
 *  * Returns the record information */
PHP_FUNCTION(ip2location_get_all)
{
	char *ip_address;
	size_t ip_len;
	IP2LocationRecord *record = NULL;

	PHP_IP2LOCATION_DB_CHECK;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip_address, &ip_len) == FAILURE) {
		return;
	}
	record = IP2Location_get_all(IP2LOCATION_G(ip2location_ptr), ip_address);
	array_init(return_value);
#if PHP_MAJOR_VERSION >= 7
	add_assoc_string(return_value, "country_short", record->country_short );
	add_assoc_string(return_value, "country_long", record->country_long);
	add_assoc_string(return_value, "region",record->region);
	add_assoc_string(return_value, "city",record->city);
	add_assoc_string(return_value, "isp",record->isp);
	add_assoc_string(return_value, "domain",record->domain);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	add_assoc_string(return_value, "zipcode",record->zip_code);
	add_assoc_string(return_value, "timezone",record->time_zone);
	add_assoc_string(return_value, "netspeed",record->net_speed);
	add_assoc_string(return_value, "iddcode",record->idd_code);
	add_assoc_string(return_value, "areacode",record->area_code);
	add_assoc_string(return_value, "weatherstationcode",record->weather_station_code);
	add_assoc_string(return_value, "weatherstationname",record->weather_station_name);
	add_assoc_string(return_value, "mobilebrand",record->mobile_brand);
	add_assoc_string(return_value, "usagetype",record->usage_type);
#else
	add_assoc_string(return_value, "zipcode",record->zipcode);
	add_assoc_string(return_value, "timezone",record->timezone);
	add_assoc_string(return_value, "netspeed",record->netspeed);
	add_assoc_string(return_value, "iddcode",record->iddcode);
	add_assoc_string(return_value, "areacode",record->areacode);
	add_assoc_string(return_value, "weatherstationcode",record->weatherstationcode);
	add_assoc_string(return_value, "weatherstationname",record->weatherstationname);
	add_assoc_string(return_value, "mobilebrand",record->mobilebrand);
	add_assoc_string(return_value, "usagetype",record->usagetype);
#endif
#if API_VERSION_NUMERIC >= 80400
	add_assoc_string(return_value, "addresstype", record->address_type);
	add_assoc_string(return_value, "category", record->category);
#endif
#if API_VERSION_NUMERIC >= 80600
	add_assoc_string(return_value, "district", record->district);
	add_assoc_string(return_value, "asn", record->asn);
	add_assoc_string(return_value, "as", record->as);
#endif
	add_assoc_string(return_value, "mcc",record->mcc);
	add_assoc_string(return_value, "mnc",record->mnc);
#else
	add_assoc_string(return_value, "country_short", record->country_short, 1);
	add_assoc_string(return_value, "country_long", record->country_long, 1);
	add_assoc_string(return_value, "region",record->region, 1);
	add_assoc_string(return_value, "city",record->city, 1);
	add_assoc_string(return_value, "isp",record->isp, 1);
	add_assoc_string(return_value, "domain",record->domain, 1);
#if API_VERSION_NUMERIC >= 80100 && API_VERSION_NUMERIC < 80104
	add_assoc_string(return_value, "zipcode",record->zip_code, 1);
	add_assoc_string(return_value, "timezone",record->time_zone, 1);
	add_assoc_string(return_value, "netspeed",record->net_speed, 1);
	add_assoc_string(return_value, "iddcode",record->idd_code, 1);
	add_assoc_string(return_value, "areacode",record->area_code, 1);
	add_assoc_string(return_value, "weatherstationcode",record->weather_station_code, 1);
	add_assoc_string(return_value, "weatherstationname",record->weather_station_name, 1);
	add_assoc_string(return_value, "mobilebrand",record->mobile_brand, 1);
	add_assoc_string(return_value, "usagetype",record->usage_type, 1);
#else
	add_assoc_string(return_value, "zipcode",record->zipcode, 1);
	add_assoc_string(return_value, "timezone",record->timezone, 1);
	add_assoc_string(return_value, "netspeed",record->netspeed, 1);
	add_assoc_string(return_value, "iddcode",record->iddcode, 1);
	add_assoc_string(return_value, "areacode",record->areacode, 1);
	add_assoc_string(return_value, "weatherstationcode",record->weatherstationcode, 1);
	add_assoc_string(return_value, "weatherstationname",record->weatherstationname, 1);
	add_assoc_string(return_value, "mobilebrand",record->mobilebrand, 1);
	add_assoc_string(return_value, "usagetype",record->usagetype, 1);
#endif
#if API_VERSION_NUMERIC >= 80400
	add_assoc_string(return_value, "addresstype", record->address_type, 1);
	add_assoc_string(return_value, "category", record->category, 1);
#endif
#if API_VERSION_NUMERIC >= 80600
	add_assoc_string(return_value, "district", record->district, 1);
	add_assoc_string(return_value, "asn", record->asn, 1);
	add_assoc_string(return_value, "as", record->as, 1);
#endif
	add_assoc_string(return_value, "mcc",record->mcc, 1);
	add_assoc_string(return_value, "mnc",record->mnc, 1);
#endif

	add_assoc_double(return_value, "latitude",record->latitude );
	add_assoc_double(return_value, "longitude",record->longitude );
	add_assoc_double(return_value, "elevation",record->elevation);
	IP2Location_free_record(record);
}
/* }}} */


/* {{{ ip2location_close()
 * Returns the record information */
PHP_FUNCTION(ip2location_close)
{
	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}
	if (IP2LOCATION_G(ip2location_ptr)) {
		IP2Location_close(IP2LOCATION_G(ip2location_ptr));
	}
	IP2LOCATION_G(ip2location_ptr) = NULL;
}
/* }}} */

/* {{{ ip2location_delete_shm()
 * Returns nothing */
PHP_FUNCTION(ip2location_delete_shm)
{
	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}
#if API_VERSION_NUMERIC >= 80100
	IP2Location_clear_memory();
#else
	IP2Location_delete_shm();
#endif
}
/* }}} */

#if API_VERSION_NUMERIC >= 80300
/* {{{ ip2location_open_mem()
 * Returns the version */
PHP_FUNCTION(ip2location_bin_version)
{
	char *version;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	PHP_IP2LOCATION_DB_CHECK;
	version  = IP2Location_bin_version(IP2LOCATION_G(ip2location_ptr));

#if PHP_MAJOR_VERSION >= 7
	RETVAL_STRING(version);
#else
	RETVAL_STRING(version, 1);
#endif
}
/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
