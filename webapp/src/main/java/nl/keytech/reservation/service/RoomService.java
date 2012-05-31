package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Room;

public interface RoomService {
	
	public List<Room> getAll();
	public Room get(String roomName);
}
