package nl.keytech.reservation.repository;

import java.util.List;
import nl.keytech.reservation.model.Group;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;

@Repository
public class GroupRepository {

	private final SessionFactory sessionFactory;

	public GroupRepository(SessionFactory sessionFactory) {
		this.sessionFactory = sessionFactory;
	}
	
	public List<Group> getAll() {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<Group>) session.createQuery("FROM Group").list();
	}
	
	public Group get(String name) {
		Session session = sessionFactory.getCurrentSession();
		
		return (Group) session.get(Group.class, name);
	}
	
	public List<Group> search(String query) {
		Session session = sessionFactory.getCurrentSession();
		
		return (List<Group>) session.createQuery("FROM Group G WHERE G.groupName LIKE :groupName ORDER BY G.groupName")
				.setParameter("groupName", query + "%")
				.setMaxResults(10).list();
	}
	
	public void save(Group group) {
		Session session = sessionFactory.getCurrentSession();

		session.saveOrUpdate(group);
	}
}