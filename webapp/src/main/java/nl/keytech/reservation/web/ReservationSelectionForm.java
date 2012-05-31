package nl.keytech.reservation.web;

import java.util.Calendar;
import nl.keytech.reservation.model.Room;

public class ReservationSelectionForm {
	private Room room;
	private Calendar startDate;
	private Calendar endDate;

	public Calendar getEndDate() {
		return endDate;
	}

	public void setEndDate(Calendar endDate) {
		this.endDate = endDate;
	}

	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}

	public Calendar getStartDate() {
		return startDate;
	}

	public void setStartDate(Calendar startDate) {
		this.startDate = startDate;
	}
}
