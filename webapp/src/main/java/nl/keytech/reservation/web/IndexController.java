package nl.keytech.reservation.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class IndexController {
	
	@RequestMapping("/")
	public String index() {
		return "redirect:reservation";
	}
	
	@RequestMapping("log")
	public String log() {
		return "log/index";
	}
}
