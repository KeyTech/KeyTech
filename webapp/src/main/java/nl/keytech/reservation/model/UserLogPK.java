package nl.keytech.reservation.model;

import java.io.Serializable;
import javax.persistence.Embeddable;

@Embeddable
public class UserLogPK implements Serializable {
	private User user;
	private Room room;

	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}

	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}

	@Override
	public boolean equals(Object obj) {
		return super.equals(obj);
	}

	@Override
	public int hashCode() {
		return super.hashCode();
	}
}
