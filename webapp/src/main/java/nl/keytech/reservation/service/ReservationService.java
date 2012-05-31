package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Reservation;

public interface ReservationService {
	
	public List<Reservation> getAll();
	public Reservation get(int identifier);
	public void save(Reservation reservation);
}
