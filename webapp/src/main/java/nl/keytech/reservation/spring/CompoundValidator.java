package nl.keytech.reservation.spring;

import java.util.List;
import java.util.Map;
import java.util.Set;
import javax.validation.ConstraintValidator;
import javax.validation.ConstraintValidatorFactory;
import javax.validation.ConstraintViolation;
import javax.validation.Validator;
import org.springframework.beans.BeansException;
import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;
import org.springframework.validation.Errors;

public class CompoundValidator implements org.springframework.validation.Validator, ApplicationContextAware,
		ConstraintValidatorFactory {

	private final Validator validator;
	private ApplicationContext applicationContext;
	private List<org.springframework.validation.Validator> springValidators;

	public CompoundValidator(Validator validator) {
		this.validator = validator;
	}

	public void setApplicationContext(ApplicationContext applicationContext) throws BeansException {
		this.applicationContext = applicationContext;
	}

	public void setSpringValidators(List<org.springframework.validation.Validator> springValidators) {
		this.springValidators = springValidators;
	}
	
	public <T extends ConstraintValidator<?, ?>> T getInstance(Class<T> key) {
		Map<String, T> beansByNames = applicationContext.getBeansOfType(key);
		if (beansByNames.isEmpty()) {
			try {
				return key.newInstance();
			} catch (InstantiationException e) {
				throw new RuntimeException("Could not instantiate constraint validator class '" + key.getName() + "'", e);
			} catch (IllegalAccessException e) {
				throw new RuntimeException("Could not instantiate constraint validator class '" + key.getName() + "'", e);
			}
		}
		if (beansByNames.size() > 1) {
			throw new RuntimeException("Only one bean of type '" + key.getName() + "' is allowed in the application context");
		}
		return (T) beansByNames.values().iterator().next();
	}

	public boolean supports(Class<?> c) {
		return true;
	}

	public void validate(Object object, Errors errors) {
		Set<ConstraintViolation<Object>> constraintViolations = validator.validate(object);
		
		for (ConstraintViolation<Object> constraintViolation : constraintViolations) {
			String propertyPath = constraintViolation.getPropertyPath().toString();
			String message = constraintViolation.getMessage();
			errors.rejectValue(propertyPath, message, message);
		}
		
		for (org.springframework.validation.Validator springValidator : springValidators) {
			if(springValidator.supports(object.getClass())) {
				springValidator.validate(object, errors);
			}
		}
	}
}
