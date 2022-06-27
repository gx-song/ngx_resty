#include <GeoIP.h>
#include <GeoIPCity.h>

struct ipinfo {
	char country_code[16];
	char country_name[16];
	char province_name[16];
	char city_name[16];
};

GeoIP *get_geoip(const char *ipfile)
{
	if (!ipfile){return NULL;}
	return GeoIP_open(ipfile,GEOIP_MEMORY_CACHE);
}
int get_ipinfo(const GeoIP *geoip,const char *ipaddress,struct ipinfo *ipinfo)
{
	char *ccode,*cname,*pname,*cityname;
	size_t ccode_len,cname_len,pname_len,cityname_len;
	ccode_len = cname_len = pname_len = cityname_len = 0;
	ccode = cname = pname = cityname = NULL;
	if (!(ipaddress && ipinfo && geoip)) {return -1;}
	memset(ipinfo,0,sizeof(struct ipinfo));
	GeoIPRecord *gir = GeoIP_record_by_addr(geoip,ipaddress);
	if (gir == NULL) {return -1;}
	ccode = gir->country_code;
	cname = gir->country_name;
	pname = GeoIP_region_name_by_code(gir->country_code,gir->region);
	cityname = gir->city;
	ccode_len = strlen(ccode)<=15?strlen(ccode):15;
	cname_len = strlen(cname)<=15?strlen(cname):15;
	pname_len = strlen(pname)<=15?strlen(pname):15;
	cityname_len = strlen(cityname)<=15?strlen(cityname):15;
	memcpy(ipinfo->country_code,ccode?ccode:"N/A",ccode_len);
	memcpy(ipinfo->country_name,cname?cname:"N/A",cname_len);
	memcpy(ipinfo->province_name,pname?pname:"N/A",pname_len);
	memcpy(ipinfo->city_name,cityname?cityname:"N/A",cityname_len);
	GeoIPRecord_delete(gir);
	return 0;
}
