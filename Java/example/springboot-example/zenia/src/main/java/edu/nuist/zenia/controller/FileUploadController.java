package edu.nuist.zenia.controller;     
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import com.alibaba.fastjson.JSONObject;

import edu.nuist.zenia.util.LocalFileUploader;


@RestController
public class FileUploadController {

    @Autowired
    private LocalFileUploader localUploader;

    @RequestMapping("/file/uploader/local/sign")
    public Map<String, String> localSign(
    ){
        return localUploader.uploadSign(  );
    }


    @RequestMapping("/file/uploader/local/upload")
	public void localUpload(
			@RequestParam MultipartFile file,
            @RequestParam String uuid,
            HttpServletResponse response,
            HttpServletRequest request
    ) throws IOException {
		JSONObject obj = localUploader.upload(uuid, file);
        PrintWriter out = response.getWriter(); 
        out.append(obj.toJSONString());
	}
}
