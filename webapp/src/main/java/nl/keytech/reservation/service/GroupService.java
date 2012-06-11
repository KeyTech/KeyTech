package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Group;

public interface GroupService {
	
	public List<Group> getAll();
	
	public Group get(String name);

	public List<Group> search(String query);
	
	public void save(Group group);
}