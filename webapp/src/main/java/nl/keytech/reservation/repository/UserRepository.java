package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.Room;
import nl.keytech.reservation.model.User;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class UserRepository {

	private final SessionFactory sessionFactory;

	public UserRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<User> getAll() {
		Session session = sessionFactory.getCurrentSession();
		
		List users = session.createQuery("FROM User").list();
		
		return (List<User>) users;
	}
	
	public List<User> search(String query) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<User>) session
				.createQuery(
					"FROM User U "
					+ "WHERE CAST(U.userIdentifier as string) LIKE :query OR U.lastname LIKE :query OR U.firstname LIKE :query "
					+ "ORDER BY U.lastname")
				.setParameter("query", query + "%")
				.setMaxResults(10).list();
	}
}