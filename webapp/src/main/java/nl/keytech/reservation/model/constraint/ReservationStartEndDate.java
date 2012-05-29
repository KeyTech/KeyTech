package nl.keytech.reservation.model.constraint;

import java.lang.annotation.Annotation;
import java.lang.annotation.Documented;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import javax.validation.Constraint;
import javax.validation.ConstraintValidator;
import javax.validation.ConstraintValidatorContext;
import javax.validation.Payload;
import nl.keytech.reservation.model.Reservation;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Constraint(validatedBy = ReservationStartEndDate.ReservationStartEndDateValidator.class)
@Documented
public @interface ReservationStartEndDate {

	String message() default "De startdatum van de reservatie mag niet voor de einddatum liggen.";

	Class<?>[] groups() default {};

	Class<? extends Payload>[] payload() default {};

	public class ReservationStartEndDateValidator implements ConstraintValidator<ReservationStartEndDate, Reservation> {

		public void initialize(ReservationStartEndDate constraintAnnotation) {
		}

		public boolean isValid(Reservation reservation, ConstraintValidatorContext context) {
			return reservation.getStartDate().before(reservation.getEndDate());
		}
	}
}
