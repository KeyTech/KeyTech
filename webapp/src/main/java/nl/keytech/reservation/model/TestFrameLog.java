package nl.keytech.reservation.model;

import java.util.Calendar;
import javax.persistence.*;

@Entity
@Table(name = "testFrameLog")
public class TestFrameLog {
	private Integer logId;
	private Room room;
	private Calendar receivedDate;

	@Id
	@Column(name = "logId")	
	public Integer getLogId() {
		return logId;
	}

	public void setLogId(Integer logId) {
		this.logId = logId;
	}
	
	@Temporal(TemporalType.TIMESTAMP)
	@Column(name = "receivedDate")
	public Calendar getReceivedDate() {
		return receivedDate;
	}

	public void setReceivedDate(Calendar receivedDate) {
		this.receivedDate = receivedDate;
	}

	@ManyToOne(targetEntity = Room.class, fetch = FetchType.EAGER)
	@JoinColumn(name = "lockIdentifier", referencedColumnName = "lockIdentifier")
	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}
}
