package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.Room;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class RoomRepository {

	private final SessionFactory sessionFactory;

	public RoomRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<Room> getAll() {
		Session session = sessionFactory.getCurrentSession();
		
		List rooms = session.createQuery("FROM Room").list();
		
		return (List<Room>) rooms;
	}
	
	public Room get(String roomName) {
		Session session = sessionFactory.getCurrentSession();
		
		return (Room) session.createQuery("FROM Room R WHERE R.roomName = :roomName").setParameter("roomName", roomName).uniqueResult();
	}
	
	public List<Room> search(String query) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<Room>) session
				.createQuery("FROM Room R WHERE R.roomName LIKE :roomName ORDER BY R.roomName")
				.setParameter("roomName", query + "%")
				.setMaxResults(10).list();		
	}
}