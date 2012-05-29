package nl.keytech.reservation.conversion;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class DateStringCalendarConvertor {
	private SimpleDateFormat format = new SimpleDateFormat("dd-MM-yyyy");

	public String convertToString(Calendar calendar) {
		return format.format(calendar.getTime());
	}
	
	public Calendar convertToCalendar(String string) throws ParseException {
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(format.parse(string));
		return calendar;
	}
}
