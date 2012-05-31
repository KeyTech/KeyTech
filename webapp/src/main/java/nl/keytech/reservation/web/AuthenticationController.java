package nl.keytech.reservation.web;

import javax.servlet.ServletRequest;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class AuthenticationController {
	
	@RequestMapping("login")
	public String create(ServletRequest request) {
		
		return "login";
	}
}
