package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.repository.ReservationRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service("reservationService")
@Transactional(propagation = Propagation.REQUIRED)
public class ReservationServiceImpl implements ReservationService {

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
	
	public void checkOverlapping(Reservation newReservation) {
		
	}
}