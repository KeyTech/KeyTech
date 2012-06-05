package nl.keytech.reservation.repository;

import java.util.Calendar;
import java.util.List;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.model.Room;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class ReservationRepository {

	private final SessionFactory sessionFactory;

	public ReservationRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<Reservation> getAll() {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<Reservation>) session.createQuery("FROM Reservation").list();
	}
	
	public Reservation get(int identifier) {
		Session session = sessionFactory.getCurrentSession();
		
		return (Reservation) session.get(Reservation.class, identifier);
	}
	
	public void save(Reservation reservation) {
		Session session = sessionFactory.getCurrentSession();

		session.saveOrUpdate(reservation);
	}
	
	public List<Reservation> getRoomReservations(Room room, Calendar startDate, Calendar endDate) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<Reservation>) session
				.createQuery("FROM Reservation r "
				+ "WHERE r.room = :room "
				+ "AND ((r.startDate BETWEEN :startDate AND :endDate) "
				+ "OR (r.endDate BETWEEN :startDate AND :endDate)"
				+ "OR (r.startDate < :startDate AND r.endDate IS NULL))")
				.setParameter("room", room)
				.setParameter("startDate", startDate)
				.setParameter("endDate", endDate).list();	
	}
	
	public Reservation getOverlappingReservation(Reservation newReservation) {
		Session session = sessionFactory.getCurrentSession();
	
		List<Reservation> reservations = (List<Reservation>) session.createSQLQuery("SELECT R1.* "
				+ "FROM reservation R1 "
				+ "INNER JOIN reservationTime RS1 ON R1.reservationTimeName = RS1.name " //, reservation R2 "
		//		+ "INNER JOIN reservationTime RS2 ON R2.reservationTimeName = RS2.name "
				+ "WHERE    R1.lockIdentifier = :lockIdentifier "
				+ " AND (:startDate BETWEEN R1.startDate AND R1.endDate OR :endDate BETWEEN R1.startDate AND R1.endDate) "
				+ " AND ((:startTime BETWEEN RS1.startTime AND RS1.endTime OR :endTime BETWEEN RS1.startTime AND RS1.endTime) "
				+ " OR  (RS1.startTime BETWEEN :startTime AND :endTime OR RS1.endTime BETWEEN :startTime AND :endTime) "
				+ " AND DAYOFWEEK(R1.startdate) = DAYOFWEEK(:startDate))"
				+ " AND R1.reservationIdentifier != :reservationIdentifier")
				.addEntity(Reservation.class)
				.setParameter("lockIdentifier", newReservation.getRoom().getLockIdentifier())
				.setParameter("startDate", newReservation.getStartDate())
				.setParameter("endDate", newReservation.getEndDate())
				.setParameter("startTime", newReservation.getReservationTime().getStartTime())
				.setParameter("endTime", newReservation.getReservationTime().getEndTime())
				.setParameter("reservationIdentifier", newReservation.getReservationIdentifier())
				.list();
		
		if(reservations.isEmpty()) {
			return null;
		}
		
		return reservations.get(0);
	}
	
	public void delete(Reservation reservation) {
		Session session = sessionFactory.getCurrentSession();
	
		session.delete(reservation);
	}
}
