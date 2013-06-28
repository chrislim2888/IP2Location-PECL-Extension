
<?php
        /*Test DB access using shared memory mathod*/ 
        ip2location_open('IP-COUNTRY-SAMPLE.BIN');
        ip2location_open_mem(IP2LOCATION_SHARED_MEMORY);
        echo ip2location_get_country_short("25.5.10.2");
        echo "\n";
        echo ip2location_get_country_long("25.5.10.2");
        echo "\n";
        echo ip2location_get_region("25.5.10.2");
        echo "\n";
        echo ip2location_get_city("25.5.10.2");
        echo "\n";
        echo ip2location_get_isp("25.5.10.2");
        echo "\n";
        echo ip2location_get_latitude("25.5.10.2");
        echo "\n";
        echo ip2location_get_longitude("25.5.10.2");
        echo "\n";
        echo ip2location_get_domain("25.5.10.2");
        echo "\n";
        echo ip2location_get_zipcode("25.5.10.2");
        echo "\n";
        echo ip2location_get_timezone("25.5.10.2");
        echo "\n";
        echo ip2location_get_netspeed("25.5.10.2");
        echo "\n";
        echo ip2location_get_iddcode("25.5.10.2");
        echo "\n";
        echo ip2location_get_areacode("25.5.10.2");
        echo "\n";
        echo ip2location_get_weatherstationcode("25.5.10.2");
        echo "\n";
        echo ip2location_get_weatherstationname("25.5.10.2");
        echo "\n";
        echo ip2location_get_mcc("25.5.10.2");
        echo "\n";
        echo ip2location_get_mnc("25.5.10.2");
        echo "\n";
        echo ip2location_get_mobilebrand("25.5.10.2");
        echo "\n";
        echo ip2location_get_elevation("25.5.10.2");
        echo "\n";
        echo ip2location_get_usagetype("25.5.10.2");
        echo "\n";
        ip2location_close();
        ip2location_delete_shm();
?>

