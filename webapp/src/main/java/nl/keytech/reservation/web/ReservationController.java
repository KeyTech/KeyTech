package nl.keytech.reservation.web;

import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.Map;
import javax.validation.Valid;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.service.ReservationService;
import nl.keytech.reservation.service.ReservationTimeService;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.InitBinder;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("reservation")
public class ReservationController {

	private final ReservationTimeService reservationTimeService;
	private final ReservationService reservationService;

	public ReservationController(ReservationTimeService reservationTimeService, ReservationService reservationService) {
		this.reservationTimeService = reservationTimeService;
		this.reservationService = reservationService;
	}

	@RequestMapping(value = "create", method = RequestMethod.POST)
	public ModelAndView create(@Valid @ModelAttribute("reservation") Reservation reservation, BindingResult bindingResult) {
		if (bindingResult.hasErrors()) {
			bindingResult.rejectValue("startDate", "walah");
			System.out.println(bindingResult.getAllErrors().get(0).toString());
			return new ModelAndView("reservation/create", "reservationTimes", reservationTimeService.getAll());
		}

		reservationService.save(reservation);

		return new ModelAndView("reservation/created");
	}

	@RequestMapping(value = "create", method = RequestMethod.GET)
	public ModelAndView createForm() {
		Map<String, Object> model = new HashMap<String, Object>();
		model.put("reservation", new Reservation());
		model.put("reservationTimes", reservationTimeService.getAll());

		return new ModelAndView("reservation/create", model);
	}

	@InitBinder
	public void initBinder(WebDataBinder binder) {
		if(binder.getTarget() instanceof Reservation) {
			((Reservation) binder.getTarget()).setCreationDate(new GregorianCalendar());
		}
	}
}