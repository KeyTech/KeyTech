package nl.keytech.reservation.web;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.Map;
import javax.validation.Valid;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.service.ReservationService;
import nl.keytech.reservation.service.ReservationTimeService;
import nl.keytech.reservation.service.RoomService;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.InitBinder;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("reservation")
public class ReservationController {

	private final ReservationTimeService reservationTimeService;
	private final ReservationService reservationService;
	private final RoomService roomService;

	public ReservationController(ReservationTimeService reservationTimeService, ReservationService reservationService, RoomService roomService) {
		this.reservationTimeService = reservationTimeService;
		this.reservationService = reservationService;
		this.roomService = roomService;
	}

	@RequestMapping(value = "create", method = RequestMethod.POST)
	public ModelAndView create(@Valid @ModelAttribute("reservation") Reservation reservation, BindingResult bindingResult) {
		Map<String, Object> model = new HashMap<String, Object>();

		if (!save(reservation, bindingResult, model)) {
			return new ModelAndView("reservation/create", model);
		}

		model.put("message", "keytech.reservation.create.success");
		return new ModelAndView("reservation/index", model);
	}
	
	@RequestMapping(value = "update/{reservationId}", method = RequestMethod.POST)
	public ModelAndView update(@PathVariable("reservationId") int reservationId, @Valid @ModelAttribute("reservation") Reservation reservation, BindingResult bindingResult) {
		Map<String, Object> model = new HashMap<String, Object>();

		if (!save(reservation, bindingResult, model)) {
			return new ModelAndView("reservation/create", model);
		}

		model.put("message", "keytech.reservation.update.success");
		return new ModelAndView("reservation/index", model);
	}

	@RequestMapping(value = "create", method = RequestMethod.GET)
	public ModelAndView createForm() {
		return getForm(new Reservation());
	}

	@RequestMapping(value = "update/{reservationId}", method = RequestMethod.GET)
	public ModelAndView updateForm(@PathVariable("reservationId") int reservationId) {
		return getForm(reservationService.get(reservationId));
	}

	private ModelAndView getForm(Reservation reservation) {
		Map<String, Object> model = new HashMap<String, Object>();
		model.put("reservation", reservation);
		model.put("reservationTimes", reservationTimeService.getAll());

		return new ModelAndView("reservation/create", model);
	}

	@RequestMapping("")
	public ModelAndView index(@ModelAttribute("form") ReservationSelectionForm form, BindingResult bindingResult) {
		Map<String, Object> model = new HashMap<String, Object>();
		model.put("rooms", roomService.getAll());

		if (form.getStartDate() == null || form.getEndDate() == null) {
			form.setStartDate(new GregorianCalendar());

			Calendar nextWeek = new GregorianCalendar();
			nextWeek.add(Calendar.WEEK_OF_YEAR, 1);
			form.setEndDate(nextWeek);
		}

		if (form.getRoom() != null) {
			model.put("reservations", reservationService.getRoomReservations(form.getRoom(), form.getStartDate(), form.getEndDate()));
		}

		return new ModelAndView("reservation/index", model);
	}
	
	@RequestMapping("delete")
	public @ResponseBody Map<String, Object> delete(@RequestParam("reservation") Integer reservationIdentifier) {
		Map<String, Object> model = new HashMap<String, Object>();
		Reservation reservation = reservationService.get(reservationIdentifier);
		
		if(reservation == null) {
			model.put("success", false);
		} else {
			reservationService.delete(reservation);
			model.put("success", true);
		}
		
		return model;
	}

	@InitBinder
	public void initBinder(WebDataBinder binder) {
		if (binder.getTarget() instanceof Reservation) {
			((Reservation) binder.getTarget()).setCreationDate(new GregorianCalendar());
		}
	}

	private boolean save(Reservation reservation, BindingResult bindingResult, Map<String, Object> model) {
		if (bindingResult.hasErrors()) {
			model.put("reservationTimes", reservationTimeService.getAll());
			return false;
		} else {
			reservationService.save(reservation);
			ReservationSelectionForm form = new ReservationSelectionForm();
			form.setRoom(reservation.getRoom());

			model.put("form", form);
			model.put("rooms", roomService.getAll());
			return true;
		}
	}
}