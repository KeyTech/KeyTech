package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Room;
import nl.keytech.reservation.repository.RoomRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service(value="roomService")
@Transactional(propagation = Propagation.REQUIRED)
public class RoomServiceImpl implements RoomService {

	private final RoomRepository roomRepository;

	public RoomServiceImpl(RoomRepository roomRepository) {
		this.roomRepository = roomRepository;
	}

	public List<Room> getAll() {
		return roomRepository.getAll();
	}

	public Room get(String roomName) {
		return roomRepository.get(roomName);
	}

	public List<Room> search(String query) {
		return roomRepository.search(query);
	}
}