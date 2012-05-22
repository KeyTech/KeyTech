package nl.keytech.reservation.web;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import nl.keytech.reservation.model.User;
import nl.keytech.reservation.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

/**
 *
 * @author stejanse
 */
@Controller
@RequestMapping("reservation")
public class ReservationController {
	
	private final UserService userService;

	public ReservationController(UserService userService) {
		this.userService = userService;
	}
	
	@RequestMapping("create")
	public ModelAndView create() {
		Map<String, Object> model = new HashMap<String, Object>();
		model.put("users", userService.getAll());
		
		return new ModelAndView("index", model); 
	}
}
