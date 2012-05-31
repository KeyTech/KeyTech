package nl.keytech.reservation.service;

import java.util.Calendar;
import java.util.List;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.model.Room;
import nl.keytech.reservation.repository.ReservationRepository;
import org.apache.log4j.Logger;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service("reservationService")
@Transactional(propagation = Propagation.REQUIRED)
public class ReservationServiceImpl implements ReservationService {
	
	private static final Logger logger = Logger.getLogger(ReservationServiceImpl.class);

	private final ReservationRepository reservationRepository;

	public ReservationServiceImpl(ReservationRepository reservationRepository) {
		this.reservationRepository = reservationRepository;
	}

	public List<Reservation> getAll() {
		return reservationRepository.getAll();
	}

	public Reservation get(int identifier) {
		return reservationRepository.get(identifier);
	}

	public void save(Reservation reservation) {
		reservationRepository.save(reservation);
	}
	
	public boolean checkOverlapping(Reservation newReservation) {
		Reservation overlappingReservation = reservationRepository.getOverlappingReservation(newReservation);
		
		if(overlappingReservation == null) {
			return false;
		}
		
		logger.info("Found overlapping reservation: " + overlappingReservation.getReservationIdentifier());	
		return true;
	}

	public List<Reservation> getRoomReservations(Room room, Calendar startDate, Calendar endDate) {
		return reservationRepository.getRoomReservations(room, startDate, endDate);
	}

	public void delete(Reservation reservation) {
		reservationRepository.delete(reservation);
	}
}