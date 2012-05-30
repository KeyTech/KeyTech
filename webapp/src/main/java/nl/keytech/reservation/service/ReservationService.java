package nl.keytech.reservation.service;

import java.util.Calendar;
import java.util.List;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.model.Room;

public interface ReservationService {
	
	public List<Reservation> getAll();
	public Reservation get(int identifier);
	public void save(Reservation reservation);
	public List<Reservation> getRoomReservations(Room room, Calendar startDate, Calendar endDate);
	public boolean checkOverlapping(Reservation newReservation);
	public void delete(Reservation reservation);
}
