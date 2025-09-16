package com.springboot;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class TestWeb {
    @RequestMapping("/first")
    public String index() {
        return new String("Hello new springboot paragram");
    }
}