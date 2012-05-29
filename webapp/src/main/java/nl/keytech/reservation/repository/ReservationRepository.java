package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.Reservation;
import nl.keytech.reservation.model.ReservationTime;
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
	
	public boolean checkOverlap(Reservation reservation) {
		Session session = sessionFactory.getCurrentSession();
	}
}
