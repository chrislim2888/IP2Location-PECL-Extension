--TEST--
DB access using cache method
--SKIPIF--
<?php
if(!extension_loaded('ip2location')) die('skip missing extension');
?>
--FILE--
<?php
/*Test DB access using file mathod*/ 
var_dump(ip2location_open(__DIR__ . '/IP-COUNTRY-SAMPLE.BIN'));
var_dump(ip2location_open_mem(IP2LOCATION_CACHE_MEMORY));
var_dump(ip2location_get_country_short('25.5.10.2'));
var_dump(ip2location_get_country_long('25.5.10.2'));
var_dump(ip2location_close());
?>
Done
--EXPECTF--
bool(true)
bool(true)
string(2) "UK"
string(14) "UNITED KINGDOM"
NULL
Done
