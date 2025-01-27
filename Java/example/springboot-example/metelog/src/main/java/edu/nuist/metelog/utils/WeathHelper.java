package edu.nuist.metelog.utils;

import java.util.HashMap;
import java.util.Map;

import org.apache.http.HttpResponse;
import org.apache.http.util.EntityUtils;

public class WeathHelper {
    private String host = "https://aliv8.data.moji.com";
	private String path = "/whapi/json/aliweather/limit";
	private String method = "POST";
	private String appcode = "9284d079f64946629b4eac03f625abad";

    public String get(double lat, double lon) {
         Map<String, String> headers = new HashMap<String, String>();
	    //最后在header中的格式(中间是英文空格)为Authorization:APPCODE 83359fd73fe94948385f570e3c139105
	    headers.put("Authorization", "APPCODE " + appcode);
	    //根据API的要求，定义相对应的Content-Type
	    headers.put("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
	    Map<String, String> querys = new HashMap<String, String>();
	    Map<String, String> bodys = new HashMap<String, String>();
	    bodys.put("lat", Double.valueOf(lat).toString());
	    bodys.put("lon", Double.valueOf(lon).toString());
	    bodys.put("token", "ff826c205f8f4a59701e64e9e64e01c4");


	    try {
	    	HttpResponse response = HttpUtils.doPost(host, path, method, headers, querys, bodys);
	    	//System.out.println(response.toString());
	    	return EntityUtils.toString(response.getEntity());
	    } catch (Exception e) {
	    	e.printStackTrace();
	    }

        return null;
    }
}
