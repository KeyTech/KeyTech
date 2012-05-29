package nl.keytech.reservation.model;

import java.sql.Time;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "reservationTime")
public class ReservationTime {

	private String name;
	private Time startTime;
	private Time endTime;

	@Id
	@Column(name = "name", length = 30)
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	@Column(name = "endTime")
	public Time getEndTime() {
		return endTime;
	}

	public void setEndTime(Time endTime) {
		this.endTime = endTime;
	}

	@Column(name = "startTime")
	public Time getStartTime() {
		return startTime;
	}

	public void setStartTime(Time startTime) {
		this.startTime = startTime;
	}
}
