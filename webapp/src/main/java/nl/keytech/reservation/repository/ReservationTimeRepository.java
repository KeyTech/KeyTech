package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.ReservationTime;
import nl.keytech.reservation.model.Room;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class ReservationTimeRepository {

	private final SessionFactory sessionFactory;

	public ReservationTimeRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<ReservationTime> getAll() {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<ReservationTime>) session.createQuery("FROM ReservationTime").list();
	}
	
	public ReservationTime get(String name) {
		Session session = sessionFactory.getCurrentSession();
		
		return (ReservationTime) session.createQuery("FROM ReservationTime R WHERE R.name = :name").setParameter("name", name).uniqueResult();
	}
}
