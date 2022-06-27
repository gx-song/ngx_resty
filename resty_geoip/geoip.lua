local cjson = require "cjson"
local ip = ''
local resut = {}
local status = 0
local country_code = ''
local country_name = ''
local province_name = ''
local city_name = ''
local args,err = ngx.req.get_uri_args()
if err == "truncated" then
	--return
end
for k,v in pairs(args) do
	if k == "ipaddress" then
		if type(v) == "table" then
			ip = v[1]
		else
			ip = v
		end
	end
end
if (ip == '') then
	status = -1
else
	local ipinfo = ffi.new("ipi[1]")
	if ( gi == nil) then
		--ngx.say ("gi is null!\n")
		status = -1
 	elseif (geoip.get_ipinfo(gi,ip,ipinfo) == -1) then
		--ngx.say("get_ipinfo : -1!\n")
		status = -1
	else
		status = 0
		country_code = ffi.string(ipinfo[0].country_code)
		country_name = ffi.string(ipinfo[0].country_name)
		province_name = ffi.string(ipinfo[0].province_name)
		city_name = ffi.string(ipinfo[0].city_name)
	end
end
local json = cjson.encode({
		ipaddress = ip,
		status = status,
		country_code = country_code,
		country_name = country_name,
		province_name = province_name,
		city_name = city_name
	})
ngx.print (json)
