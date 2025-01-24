package edu.nuist.zenia.util;

import com.alibaba.fastjson.JSONObject;
import com.google.common.io.Files;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

@Component
public class LocalFileUploader{

    @Value("${root.db}")
    private String dbRoot;

    @Value("${root.file}")
    private String filedir;

    public Map<String, String> uploadSign( ) {
        Map<String, String> rst = new HashMap<>();
        rst.put("uuid", UUID.randomUUID().toString());
        return rst;
    }


    //本地接收文件上传
    public JSONObject upload(
        String uuid,
        MultipartFile file
    ){
        JSONObject obj = new JSONObject();
        try {
        	String ext = file.getOriginalFilename();
        	
        	ext = ext.substring(ext.lastIndexOf(".") ) ;
            byte[] bytes = file.getBytes();            
            String fileName = uuid;
            File targetFile = new File( dbRoot + "/" + filedir +"/"+ fileName);
            
            Files.write(bytes, targetFile);
            
            obj.put("origin", file.getOriginalFilename());
            obj.put("inner", fileName);
            obj.put("flag", true);
            return obj;
        } catch (IOException e) {
            e.printStackTrace();
        }
        obj.put("flag", false);
        return null;
    }
    
}
