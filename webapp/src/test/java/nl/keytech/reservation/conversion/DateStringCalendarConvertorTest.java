package nl.keytech.reservation.conversion;

import java.util.Calendar;
import java.util.GregorianCalendar;
import org.junit.*;
import static org.junit.Assert.*;

public class DateStringCalendarConvertorTest {
	
	@Test
	public void testConvertToString() {
		Calendar calendar = new GregorianCalendar(2012, Calendar.MAY, 2);
		DateStringCalendarConvertor instance = new DateStringCalendarConvertor();
		
		String expResult = "02-05-2012";
		String result = instance.convertToString(calendar);
		
		assertEquals(expResult, result);
	}

	@Test
	public void testConvertToCalendar() throws Exception {
		String string = "02-05-2012";
		DateStringCalendarConvertor instance = new DateStringCalendarConvertor();

		Calendar result = instance.convertToCalendar(string);
		
		assertNotNull(result);
		assertEquals(2, result.get(Calendar.DAY_OF_MONTH));
		assertEquals(Calendar.MAY, result.get(Calendar.MONTH));
		assertEquals(2012, result.get(Calendar.YEAR));		
	}
}
