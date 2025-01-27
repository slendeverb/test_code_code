package edu.nuist.zenia.controller;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class PageRouter {
    public static String USER_CACHE = "USER_CACHE";

    @RequestMapping("/")
    public String index() {
        return "index";
    }

    @RequestMapping("/exit")
    @ResponseBody
    public void exit(HttpServletRequest request) {
        request.getSession().removeAttribute(USER_CACHE);
        return ;
    }

    @RequestMapping("/admin")
    public String admin(
        HttpServletRequest request
    ) {

        Object o = request.getSession().getAttribute(USER_CACHE);
        if( o == null){
            return "login";
        }
        return "admin";
    }

    @RequestMapping("/login")
    public String login() {
        return "login";
    }

    @Value("${user.username}")
    private String username;

    @Value("${user.password}")
    private String password;

    @RequestMapping("/user/login")
    @ResponseBody
    public String loginDo(
        HttpServletRequest request,
        String un,
        String ps
    ) {

        if( username.trim().equals(un.trim()) && password.trim().equals(ps.trim())){
            request.getSession().setAttribute(USER_CACHE, username);
            return "true";
        }
        return "false";
    }
}
