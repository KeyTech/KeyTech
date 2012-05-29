package nl.keytech.reservation.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.UniqueConstraint;

@Entity
@Table(name = "room", uniqueConstraints = {@UniqueConstraint(columnNames = "roomName")})
public class Room {

	private short lockIdentifier;
	private String roomName;

	@Id
	@Column(name = "lockIdentifier")
	public short getLockIdentifier() {
		return lockIdentifier;
	}

	public void setLockIdentifier(short lockIdentifier) {
		this.lockIdentifier = lockIdentifier;
	}

	@Column(name = "roomName", length = 30)
	public String getRoomName() {
		return roomName;
	}

	public void setRoomName(String roomName) {
		this.roomName = roomName;
	}
}
