package nl.keytech.reservation.conversion;

public interface ObjectConvertor {
	public Class getFrom();

	public void setFrom(Class from);

	public Class getTo();

	public void setTo(Class to);
	
	public Object convert(Object from);
}
