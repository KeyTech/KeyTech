package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.Group;
import nl.keytech.reservation.model.TestFrameLog;
import nl.keytech.reservation.model.UserLog;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class LogRepository {
	private final SessionFactory sessionFactory;

	public LogRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<TestFrameLog> getLastTestFrameLog(int number) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<TestFrameLog>) session.createQuery("FROM TestFrameLog L ORDER BY L.receivedDate")
				.setMaxResults(number).list();
	}
	
	public List<UserLog> getLastUserLogs(int number) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<UserLog>) session.createQuery("FROM UserLog L ORDER BY L.logDate")
				.setMaxResults(number).list();
	}
}
