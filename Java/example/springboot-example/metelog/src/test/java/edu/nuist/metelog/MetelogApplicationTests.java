package edu.nuist.metelog;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


import org.apache.http.HttpResponse;
import org.apache.http.util.EntityUtils;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import edu.nuist.metelog.entity.Location;
import edu.nuist.metelog.entity.LocationService;
import edu.nuist.metelog.entity.Weath;
import edu.nuist.metelog.entity.WeathService;
import edu.nuist.metelog.utils.HttpUtils;
import edu.nuist.metelog.utils.WeathHelper;


@SpringBootTest
class MetelogApplicationTests {

	// 测试上下文加载，通常用于验证Spring应用上下文是否正确加载
	@Test
	void contextLoads() {
	}

	// 测试方法test1，打印"test1"到控制台

	@Autowired 
	LocationService locationService;

	@Autowired 
	WeathService weathService;


	@Test
	public void testWeath(){
		WeathHelper weathHelper = new WeathHelper();
		Location l = locationService.findById(3);

		String info = weathHelper.get(l.getLat(), l.getLon());

		Weath w = new Weath();
		w.setLid(3);
		w.setInfo(info);

		weathService.save(w);
	}

	@Test
	public void test1() {
		Location location = new Location();
		location.setLat(39.91488908);
		location.setLon(116.40387397);
		location.setDirect("东城区");
		location.setPrince("北京");

		locationService.save(location);		
		// Location l = locationService.findById(2);
		//locationService.deleteById(1);
		//System.out.println(l);
	}


	// 测试方法test，用于发送HTTP POST请求并处理响应
	@Test
	public void test() throws IOException{

 		String host = "https://aliv8.data.moji.com";
	    String path = "/whapi/json/aliweather/limit";
	    String method = "POST";
	    String appcode = "9284d079f64946629b4eac03f625abad";
	    Map<String, String> headers = new HashMap<String, String>();
	    //最后在header中的格式(中间是英文空格)为Authorization:APPCODE 83359fd73fe94948385f570e3c139105
	    headers.put("Authorization", "APPCODE " + appcode);
	    //根据API的要求，定义相对应的Content-Type
	    headers.put("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
	    Map<String, String> querys = new HashMap<String, String>();
	    Map<String, String> bodys = new HashMap<String, String>();
	    bodys.put("lat", "39.91488908");
	    bodys.put("lon", "116.40387397");
	    bodys.put("token", "ff826c205f8f4a59701e64e9e64e01c4");


	    try {
	    	/**
	    	* 重要提示如下:
	    	* HttpUtils请从
	    	* https://github.com/aliyun/api-gateway-demo-sign-java/blob/master/src/main/java/com/aliyun/api/gateway/demo/util/HttpUtils.java
	    	* 下载
	    	*
	    	* 相应的依赖请参照
	    	* https://github.com/aliyun/api-gateway-demo-sign-java/blob/master/pom.xml
	    	*/
	    	HttpResponse response = HttpUtils.doPost(host, path, method, headers, querys, bodys);
	    	System.out.println(response.toString());
	    	//获取response的body
	    	System.out.println(EntityUtils.toString(response.getEntity()));
	    } catch (Exception e) {
	    	e.printStackTrace();
	    }
			
	}

}
