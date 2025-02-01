package org.test;

import java.util.HashMap;
import java.util.Map;

public class App {

    public static void main(String[] args) {
        String host="https://aliv8.data.moji.com";
        String path="/whapi/json/aliweather/limit";
        String method="POST";
        String appcode="";

        Map<String,String> headers=new HashMap<>();
        headers.put("Authorization", "APPCODE "+appcode);
        headers.put("Content-Type", "application/x-www-form-urlencoded; charset=utf-8");
        Map<String,String> querys=new HashMap<>();
        Map<String,String> bodys=new HashMap<>();
        bodys.put("lat", "39.906217");
        bodys.put("lon", "116.3912757");
        bodys.put("token", "");
    }
}