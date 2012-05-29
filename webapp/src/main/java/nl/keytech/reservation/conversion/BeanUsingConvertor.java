package nl.keytech.reservation.conversion;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import org.apache.log4j.Logger;

public class BeanUsingConvertor implements ObjectConvertor {
	private Logger logger = Logger.getLogger(this.getClass());

	private Class from;
	private Class to;
	private Object conversionBean;
	private String conversionMethod;

	public Object getConversionBean() {
		return conversionBean;
	}

	public void setConversionBean(Object conversionBean) {
		this.conversionBean = conversionBean;
	}

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
			Class convertorClass = this.getConversionBean().getClass();
			Method convertorMethod = convertorClass.getDeclaredMethod(this.getConversionMethod(), this.getFrom());
			return convertorMethod.invoke(this.getConversionBean(), from);
		} catch (InvocationTargetException ex) {
			logger.info("The conversion bean " + this.getConversionBean().getClass().getName()
					+ " throwed an exception after the conversion method " + this.getConversionMethod()
					+ " was called.", ex.getTargetException());

		} catch (Exception ex) {
			logger.error("Could not convert object due configuration problem, convertor bean: "
					+ this.getConversionBean().getClass().getName(), ex);
		}
		
		return null;
	}
}
