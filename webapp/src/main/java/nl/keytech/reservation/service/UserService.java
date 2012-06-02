package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.User;

public interface UserService {
	
	public List<User> getAll();
	
	public List<User> search(String query);
}
