<?php

/**
 * @generate-function-entries
 * @generate-legacy-arginfo
 */

function ip2location_open(string $file_path): bool {}
function ip2location_open_mem(int $method): bool {}
function ip2location_get_country_short(string $ip_address): string {}
function ip2location_get_country_long(string $ip_address): string {}
function ip2location_get_region(string $ip_address): string {}
function ip2location_get_city(string $ip_address): string {}
function ip2location_get_isp(string $ip_address): string {}
function ip2location_get_latitude(string $ip_address): string {}
function ip2location_get_longitude(string $ip_address): string {}
function ip2location_get_domain(string $ip_address): string {}
function ip2location_get_zipcode(string $ip_address): string {}
function ip2location_get_timezone(string $ip_address): string {}
function ip2location_get_netspeed(string $ip_address): string {}
function ip2location_get_iddcode(string $ip_address): string {}
function ip2location_get_areacode(string $ip_address): string {}
function ip2location_get_weatherstationcode(string $ip_address): string {}
function ip2location_get_weatherstationname(string $ip_address): string {}
function ip2location_get_mcc(string $ip_address): string {}
function ip2location_get_mnc(string $ip_address): string {}
function ip2location_get_mobilebrand(string $ip_address): string {}
function ip2location_get_elevation(string $ip_address): string {}
function ip2location_get_usagetype(string $ip_address): string {}
function ip2location_get_all(string $ip_address): array {}
function ip2location_close(): void {}
function ip2location_delete_shm(): void {}
#if API_VERSION_NUMERIC >= 80300
function ip2location_bin_version(): string {}
#endif
#if API_VERSION_NUMERIC >= 80400
function ip2location_get_addresstype(string $ip_address): string {}
function ip2location_get_category(string $ip_address): string {}
#endif
#if API_VERSION_NUMERIC >= 80600
function ip2location_get_district(string $ip_address): string {}
function ip2location_get_asn(string $ip_address): string {}
function ip2location_get_as(string $ip_address): string {}
#endif
#if API_VERSION_NUMERIC >= 80700
function ip2location_get_as_domain(string $ip_address): string {}
function ip2location_get_as_usage_type(string $ip_address): string {}
function ip2location_get_as_cidr(string $ip_address): string {}
#endif
