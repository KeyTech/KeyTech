package nl.keytech.reservation.conversion;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import org.apache.log4j.Logger;

public class SelfConvertor implements ObjectConvertor {
	private Logger logger = Logger.getLogger(this.getClass());

	private Class from;
	private Class to;
	private String conversionMethod;

	public String getConversionMethod() {
		return conversionMethod;
	}

	public void setConversionMethod(String conversionMethod) {
		this.conversionMethod = conversionMethod;
	}

	public Class getFrom() {
		return from;
	}

	public void setFrom(Class from) {
		this.from = from;
	}

	public Class getTo() {
		return to;
	}

	public void setTo(Class to) {
		this.to = to;
	}

	public Object convert(Object from) {
		try {
			Method convertorMethod = from.getClass().getDeclaredMethod(this.getConversionMethod());
			return convertorMethod.invoke(from);
		} catch (InvocationTargetException ex) {
			logger.info("The self converting object " + from.getClass().getName()
					+ " throwed an exception after the conversion method " + this.getConversionMethod()
					+ " was called.", ex.getTargetException());

		} catch (Exception ex) {
			logger.error("Could not convert object due configuration problem, object to convert: "
					+ from.getClass().getName(), ex);
		}
		
		return null;
	}
}
