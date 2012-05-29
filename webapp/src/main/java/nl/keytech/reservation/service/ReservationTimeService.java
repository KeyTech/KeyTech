package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.ReservationTime;

public interface ReservationTimeService {
	
	public List<ReservationTime> getAll();
	public ReservationTime get(String name);
}
