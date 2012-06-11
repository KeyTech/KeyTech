package nl.keytech.reservation.web;

import java.util.List;
import nl.keytech.reservation.model.User;
import nl.keytech.reservation.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("user")
public class UserController {
	
	private final UserService userService;

	public UserController(UserService userService) {
		this.userService = userService;
	}
	
	@RequestMapping("searchAjax")
	public @ResponseBody List<User> searchAjax(@RequestParam("query") String query) {
		return userService.search(query);
	}
}