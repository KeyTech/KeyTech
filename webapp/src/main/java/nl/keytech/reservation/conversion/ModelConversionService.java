package nl.keytech.reservation.conversion;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.List;
import org.apache.log4j.Logger;
import org.springframework.core.convert.ConversionService;
import org.springframework.core.convert.TypeDescriptor;

public class ModelConversionService implements ConversionService {

	private Logger logger = Logger.getLogger(this.getClass());
	private List<ObjectConvertor> convertors;

	public List<ObjectConvertor> getConvertors() {
		return convertors;
	}

	public void setConvertors(List<ObjectConvertor> convertors) {
		this.convertors = convertors;
	}

	public boolean canConvert(Class<?> sourceType, Class<?> targetType) {
		for (ObjectConvertor convertor : convertors) {
			if (convertor.getFrom().equals(sourceType) && convertor.getTo().equals(targetType)) {
				return true;
			}
		}

		return false;
	}

	public boolean canConvert(TypeDescriptor sourceType, TypeDescriptor targetType) {
		return canConvert(sourceType.getObjectType(), targetType.getObjectType());
	}

	public <T> T convert(Object source, Class<T> targetType) {
		if(source== null) {
			return null;
		}
		
		for (ObjectConvertor convertor : convertors) {
			if (convertor.getFrom().isInstance(source) && convertor.getTo().equals(targetType)) {
				return (T) convertor.convert(source);
			}

		}

		logger.error("No convertor found for converting " + source.getClass().getName() + " to " + targetType.getName() + ".");
		return null;
	}

	public Object convert(Object source, TypeDescriptor sourceType, TypeDescriptor targetType) {
		return convert(source, targetType.getObjectType());
	}
}