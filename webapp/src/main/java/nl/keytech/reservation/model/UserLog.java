package nl.keytech.reservation.model;

import java.io.Serializable;
import java.util.Calendar;
import javax.persistence.*;
import nl.keytech.reservation.model.enums.UserLogType;

@Entity
@Table(name = "userLog")
@IdClass(UserLogPK.class)
public class UserLog implements Serializable {

	private User user;
	private Room room;
	private Calendar logDate;
	private UserLogType result;

	@Temporal(TemporalType.TIMESTAMP)
	@Column(name = "logDate")
	public Calendar getLogDate() {
		return logDate;
	}

	public void setLogDate(Calendar logDate) {
		this.logDate = logDate;
	}

	@Enumerated(EnumType.STRING)
	@Column(name="result", columnDefinition = "enum('PERMISSION_GRANTED','INCORRECT_ID','NO_ACCESS','USER_BLOCKED')")
	public UserLogType getResult() {
		return result;
	}

	public void setResult(UserLogType result) {
		this.result = result;
	}

	@Id
	@ManyToOne(targetEntity = Room.class, fetch = FetchType.EAGER)
	@JoinColumn(name = "lockIdentifier", referencedColumnName = "lockIdentifier")
	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}

	@Id
	@ManyToOne(targetEntity = User.class, fetch = FetchType.EAGER)
	@JoinColumn(name = "userIdentifier", referencedColumnName = "userIdentifier")
	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}
}