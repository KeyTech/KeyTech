package nl.keytech.reservation.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 *
 * @author stejanse
 */
@Controller
@RequestMapping("reservation")
public class ReservationController {
	
	@RequestMapping("create")
	public String create() {
		return "index"; 
	}
}
