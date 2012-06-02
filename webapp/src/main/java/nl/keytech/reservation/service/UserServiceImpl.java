package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.User;
import nl.keytech.reservation.repository.UserRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service
@Transactional(propagation = Propagation.REQUIRED)
public class UserServiceImpl implements UserService {

	private final UserRepository userRepository;

	public UserServiceImpl(UserRepository userRepository) {
		this.userRepository = userRepository;
	}

	public List<User> getAll() {
		return userRepository.getAll();
	}

	public List<User> search(String query) {
		return userRepository.search(query);
	}
}