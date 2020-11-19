--TEST--
DB access using shared memory method
--SKIPIF--
<?php
if(!extension_loaded('ip2location')) die('skip missing extension');
?>
--FILE--
<?php
/*Test DB access using file mathod*/ 
var_dump(ip2location_open(__DIR__ . '/IP-COUNTRY-SAMPLE.BIN'));
var_dump(ip2location_open_mem(IP2LOCATION_SHARED_MEMORY));
var_dump(ip2location_get_country_short('25.5.10.2'));
var_dump(ip2location_get_country_long('25.5.10.2'));
var_dump(IP2Location_delete_shm());
var_dump(ip2location_close());
?>
Done
--EXPECTF--
bool(true)
bool(true)
string(2) "UK"
string(14) "UNITED KINGDOM"
NULL
NULL
Done
