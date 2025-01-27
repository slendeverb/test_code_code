package edu.nuist.zenia.controller;  


import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class PopController {
    @RequestMapping("/pop/msg/{type}/{msg}")
    public String msgbox( Model model, @PathVariable String type, @PathVariable String msg ){
        model.addAttribute( "msgbox",  true );
        model.addAttribute( "type",  type );
        model.addAttribute( "msg",  msg );
        return "popup/poptemplate";
    }

    @RequestMapping("/pop/confirm/{title}/{msg}")
    public String confirm( Model model,@PathVariable String title, @PathVariable String msg ){
        model.addAttribute( "confirm",  true );
        model.addAttribute( "title",  title );
        model.addAttribute( "msg",  msg );
        return "popup/poptemplate";
    }

    @RequestMapping("/pop/{window}")
    public String pop( Model model, @PathVariable String window ){
        model.addAttribute( window,  true );
        return "popup/poptemplate";
    }

}
