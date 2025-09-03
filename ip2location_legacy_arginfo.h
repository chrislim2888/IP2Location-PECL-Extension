/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: c57e18a606ee629525559e7f245e9643c54c59c5 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_open, 0, 0, 1)
	ZEND_ARG_INFO(0, file_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_open_mem, 0, 0, 1)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_get_country_short, 0, 0, 1)
	ZEND_ARG_INFO(0, ip_address)
ZEND_END_ARG_INFO()

#define arginfo_ip2location_get_country_long arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_region arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_city arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_isp arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_latitude arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_longitude arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_domain arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_zipcode arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_timezone arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_netspeed arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_iddcode arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_areacode arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_weatherstationcode arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_weatherstationname arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_mcc arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_mnc arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_mobilebrand arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_elevation arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_usagetype arginfo_ip2location_get_country_short

#define arginfo_ip2location_get_all arginfo_ip2location_get_country_short

ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_close, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_ip2location_delete_shm arginfo_ip2location_close

#if API_VERSION_NUMERIC >= 80300
ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_bin_version, 0, 0, 0)
ZEND_END_ARG_INFO()
#endif

#if API_VERSION_NUMERIC >= 80400
ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_get_addresstype, 0, 0, 1)
	ZEND_ARG_INFO(0, ip_address)
ZEND_END_ARG_INFO()
#endif

#if API_VERSION_NUMERIC >= 80400
#define arginfo_ip2location_get_category arginfo_ip2location_get_addresstype
#endif

#if API_VERSION_NUMERIC >= 80600
ZEND_BEGIN_ARG_INFO_EX(arginfo_ip2location_get_district, 0, 0, 1)
	ZEND_ARG_INFO(0, ip_address)
ZEND_END_ARG_INFO()
#endif

#if API_VERSION_NUMERIC >= 80600
#define arginfo_ip2location_get_asn arginfo_ip2location_get_asn
#endif

#if API_VERSION_NUMERIC >= 80600
#define arginfo_ip2location_get_as arginfo_ip2location_get_as
#endif

#if API_VERSION_NUMERIC >= 80700
#define arginfo_ip2location_get_as_domain arginfo_ip2location_get_domain
#endif

#if API_VERSION_NUMERIC >= 80700
#define arginfo_ip2location_get_as_usage_type arginfo_ip2location_get_usage_type
#endif

#if API_VERSION_NUMERIC >= 80700
#define arginfo_ip2location_get_as_cidr arginfo_ip2location_get_cidr
#endif


ZEND_FUNCTION(ip2location_open);
ZEND_FUNCTION(ip2location_open_mem);
ZEND_FUNCTION(ip2location_get_country_short);
ZEND_FUNCTION(ip2location_get_country_long);
ZEND_FUNCTION(ip2location_get_region);
ZEND_FUNCTION(ip2location_get_city);
ZEND_FUNCTION(ip2location_get_isp);
ZEND_FUNCTION(ip2location_get_latitude);
ZEND_FUNCTION(ip2location_get_longitude);
ZEND_FUNCTION(ip2location_get_domain);
ZEND_FUNCTION(ip2location_get_zipcode);
ZEND_FUNCTION(ip2location_get_timezone);
ZEND_FUNCTION(ip2location_get_netspeed);
ZEND_FUNCTION(ip2location_get_iddcode);
ZEND_FUNCTION(ip2location_get_areacode);
ZEND_FUNCTION(ip2location_get_weatherstationcode);
ZEND_FUNCTION(ip2location_get_weatherstationname);
ZEND_FUNCTION(ip2location_get_mcc);
ZEND_FUNCTION(ip2location_get_mnc);
ZEND_FUNCTION(ip2location_get_mobilebrand);
ZEND_FUNCTION(ip2location_get_elevation);
ZEND_FUNCTION(ip2location_get_usagetype);
ZEND_FUNCTION(ip2location_get_all);
ZEND_FUNCTION(ip2location_close);
ZEND_FUNCTION(ip2location_delete_shm);
#if API_VERSION_NUMERIC >= 80300
ZEND_FUNCTION(ip2location_bin_version);
#endif
#if API_VERSION_NUMERIC >= 80400
ZEND_FUNCTION(ip2location_get_addresstype);
#endif
#if API_VERSION_NUMERIC >= 80400
ZEND_FUNCTION(ip2location_get_category);
#endif
#if API_VERSION_NUMERIC >= 80600
ZEND_FUNCTION(ip2location_get_district);
#endif
#if API_VERSION_NUMERIC >= 80600
ZEND_FUNCTION(ip2location_get_asn);
#endif
#if API_VERSION_NUMERIC >= 80600
ZEND_FUNCTION(ip2location_get_as);
#endif


static const zend_function_entry ext_functions[] = {
	ZEND_FE(ip2location_open, arginfo_ip2location_open)
	ZEND_FE(ip2location_open_mem, arginfo_ip2location_open_mem)
	ZEND_FE(ip2location_get_country_short, arginfo_ip2location_get_country_short)
	ZEND_FE(ip2location_get_country_long, arginfo_ip2location_get_country_long)
	ZEND_FE(ip2location_get_region, arginfo_ip2location_get_region)
	ZEND_FE(ip2location_get_city, arginfo_ip2location_get_city)
	ZEND_FE(ip2location_get_isp, arginfo_ip2location_get_isp)
	ZEND_FE(ip2location_get_latitude, arginfo_ip2location_get_latitude)
	ZEND_FE(ip2location_get_longitude, arginfo_ip2location_get_longitude)
	ZEND_FE(ip2location_get_domain, arginfo_ip2location_get_domain)
	ZEND_FE(ip2location_get_zipcode, arginfo_ip2location_get_zipcode)
	ZEND_FE(ip2location_get_timezone, arginfo_ip2location_get_timezone)
	ZEND_FE(ip2location_get_netspeed, arginfo_ip2location_get_netspeed)
	ZEND_FE(ip2location_get_iddcode, arginfo_ip2location_get_iddcode)
	ZEND_FE(ip2location_get_areacode, arginfo_ip2location_get_areacode)
	ZEND_FE(ip2location_get_weatherstationcode, arginfo_ip2location_get_weatherstationcode)
	ZEND_FE(ip2location_get_weatherstationname, arginfo_ip2location_get_weatherstationname)
	ZEND_FE(ip2location_get_mcc, arginfo_ip2location_get_mcc)
	ZEND_FE(ip2location_get_mnc, arginfo_ip2location_get_mnc)
	ZEND_FE(ip2location_get_mobilebrand, arginfo_ip2location_get_mobilebrand)
	ZEND_FE(ip2location_get_elevation, arginfo_ip2location_get_elevation)
	ZEND_FE(ip2location_get_usagetype, arginfo_ip2location_get_usagetype)
	ZEND_FE(ip2location_get_all, arginfo_ip2location_get_all)
	ZEND_FE(ip2location_close, arginfo_ip2location_close)
	ZEND_FE(ip2location_delete_shm, arginfo_ip2location_delete_shm)
#if API_VERSION_NUMERIC >= 80300
	ZEND_FE(ip2location_bin_version, arginfo_ip2location_bin_version)
#endif
#if API_VERSION_NUMERIC >= 80400
	ZEND_FE(ip2location_get_addresstype, arginfo_ip2location_get_addresstype)
#endif
#if API_VERSION_NUMERIC >= 80400
	ZEND_FE(ip2location_get_category, arginfo_ip2location_get_category)
#endif
#if API_VERSION_NUMERIC >= 80600
	ZEND_FE(ip2location_get_district, arginfo_ip2location_get_district)
#endif
#if API_VERSION_NUMERIC >= 80600
	ZEND_FE(ip2location_get_asn, arginfo_ip2location_get_asn)
#endif
#if API_VERSION_NUMERIC >= 80600
	ZEND_FE(ip2location_get_as, arginfo_ip2location_get_as)
#endif
	ZEND_FE_END
};
