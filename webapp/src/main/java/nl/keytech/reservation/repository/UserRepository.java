package nl.keytech.reservation.repository;

import java.util.List;
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
}