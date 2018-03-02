# IP2Location PECL Extension
This PECL extension allows you to find the location of an IP address - country, region or state, city, latitude and longitude, US ZIP code, time zone, Internet Service Provider (ISP) or company name, domain name, net speed, area code, weather station code, weather station name, mobile country code (MCC), mobile network code (MNC) and carrier brand, elevation, and usage type.

To compile it, you will need to have the ip2location c library (version 8.x) installed.

# Installation

### Install IP2Location C Library (on Linux/Unix)
1. Download the latest ip2location c libray at https://www.ip2location.com/developers/c
2. Decompress the archive.
3. Navigate to working directory. example, cd ip2location-c-x.x.x
4. autoreconf -i -v --force
5. ./configure
6. make
7. make install
    
### Install PECL extension (on Linux/Unix)
1. Decompress the archive.
2. Navigate to working directory.
3. phpize
4. ./configure
5. make
6. make install
7. A successful install will have created ip2location.so and put it into the PHP extensions directory.
8. Open the php.ini file, and add an extension=ip2loation.so line.
9. Restart apache server. Example, /etc/init.d/apache2 restart
10. php -m (You should notice the ip2location module in the list)

For details installation instructions for PHP PECL extensions, please see:
http://www.php.net/manual/en/install.pecl.php

# Sample BIN Databases
* Download free IP2Location LITE databases at [https://lite.ip2location.com](https://lite.ip2location.com)  
* Download IP2Location sample databases at [https://www.ip2location.com/developers](https://www.ip2location.com/developers)

# IPv4 BIN vs IPv6 BIN
* Use the IPv4 BIN file if you just need to query IPv4 addresses.
* Use the IPv6 BIN file if you need to query BOTH IPv4 and IPv6 addresses.

# Support
Email: support@ip2location.com.  
URL: [http://www.ip2location.com](http://www.ip2location.com)
