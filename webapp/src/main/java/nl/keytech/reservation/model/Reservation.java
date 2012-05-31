package nl.keytech.reservation.model;

import java.util.Calendar;
import javax.persistence.*;
import javax.validation.constraints.NotNull;
import nl.keytech.reservation.model.constraint.ReservationStartEndDate;

@ReservationStartEndDate
@Entity
@Table(name = "reservation", uniqueConstraints=@UniqueConstraint(columnNames={"groupName", "lockIdentifier", "startDate"}))
public class Reservation {

	public enum Interval {
		DAY, WEEK, MONTH
	};
	private int reservationIdentifier;
	private Group group;
	private Room room;
	private Calendar creationDate;
	private Interval interval;
	private Calendar startDate;
	private Calendar endDate;
	private ReservationTime reservationTime;

	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	@Column(name = "reservationIdentifier")
	public int getReservationIdentifier() {
		return reservationIdentifier;
	}

	public void setReservationIdentifier(int reservationIdentifier) {
		this.reservationIdentifier = reservationIdentifier;
	}

	@NotNull
	@ManyToOne
	@JoinColumn(name = "groupName", referencedColumnName = "groupName")
	public Group getGroup() {
		return group;
	}

	public void setGroup(Group group) {
		this.group = group;
	}

	@NotNull
	@ManyToOne
	@JoinColumn(name = "lockIdentifier", referencedColumnName = "lockIdentifier")
	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}

	@NotNull
	@Column(name = "creationDate")
	@Temporal(TemporalType.TIMESTAMP)
	public Calendar getCreationDate() {
		return creationDate;
	}

	public void setCreationDate(Calendar creationDate) {
		this.creationDate = creationDate;
	}

	@NotNull
	@Enumerated(EnumType.STRING)
	@Column(name = "repeatInterval", columnDefinition = "ENUM('DAY', 'WEEK', 'MONTH')")
	public Interval getInterval() {
		return interval;
	}

	public void setInterval(Interval interval) {
		this.interval = interval;
	}

	@Column(name = "endDate")
	@Temporal(TemporalType.TIMESTAMP)
	public Calendar getEndDate() {
		return endDate;
	}

	public void setEndDate(Calendar endDate) {
		this.endDate = endDate;
	}

	@NotNull
	@Column(name = "startDate")
	@Temporal(TemporalType.TIMESTAMP)
	public Calendar getStartDate() {
		return startDate;
	}

	public void setStartDate(Calendar startDate) {
		this.startDate = startDate;
	}

	@NotNull
	@ManyToOne
	@JoinColumn(name = "reservationTimeName", referencedColumnName = "name")
	public ReservationTime getReservationTime() {
		return reservationTime;
	}

	public void setReservationTime(ReservationTime reservationTime) {
		this.reservationTime = reservationTime;
	}
}
