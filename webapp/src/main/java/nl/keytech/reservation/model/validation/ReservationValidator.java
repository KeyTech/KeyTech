package nl.keytech.reservation.model.validation;

import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.service.ReservationService;
import org.springframework.validation.Errors;
import org.springframework.validation.Validator;

public class ReservationValidator implements Validator {
	
	private final ReservationService reservationService;

	public ReservationValidator(ReservationService reservationService) {
		this.reservationService = reservationService;
	}

	public boolean supports(Class<?> clazz) {
		return Reservation.class.equals(clazz);
	}

	public void validate(Object target, Errors errors) {
		Reservation reservation = (Reservation) target;
		
		if(reservation.getEndDate() != null && reservation.getStartDate().after(reservation.getEndDate())) {
			errors.rejectValue("startDate", "keytech.reservation.startDate.afterEndDate");
		}
		
		if(errors.hasErrors() == false && reservationService.checkOverlapping(reservation)) {
			errors.rejectValue("startDate", "keytech.reservation.startDate.overlaps");
		}
	}
	
}