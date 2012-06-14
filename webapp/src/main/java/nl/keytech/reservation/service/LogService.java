package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.UserLog;

public interface LogService {
	public List<UserLog> getLastUserLogs(int number);
}