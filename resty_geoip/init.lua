ffi = require "ffi"
ffi.cdef [[ 
	typedef struct ipinfo {char country_code[16],country_name[16],province_name[16],city_name[16];} ipi;
	void *get_geoip(const char *ipfile);
	int get_ipinfo(const void *getoip,const char *ipaddress,struct ipinfo *ipinfo);
	void GeoIP_delete(void *gi);
]]
geoip = ffi.load("./libgeoip.so")
if gi then
	GeoIP_delete(gi)
end
gi = geoip.get_geoip("./GeoLiteCity.dat")

