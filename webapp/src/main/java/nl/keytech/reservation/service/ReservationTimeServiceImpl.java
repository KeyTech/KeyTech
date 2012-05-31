package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.ReservationTime;
import nl.keytech.reservation.repository.ReservationTimeRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service("reservationTimeService")
@Transactional(propagation = Propagation.REQUIRED)
public class ReservationTimeServiceImpl implements ReservationTimeService {

	private final ReservationTimeRepository reservationTimeRepository;

	public ReservationTimeServiceImpl(ReservationTimeRepository reservationTimeRepository) {
		this.reservationTimeRepository = reservationTimeRepository;
	}

	public List<ReservationTime> getAll() {
		return reservationTimeRepository.getAll();
	}

	public ReservationTime get(String name) {
		return reservationTimeRepository.get(name);
	}
}