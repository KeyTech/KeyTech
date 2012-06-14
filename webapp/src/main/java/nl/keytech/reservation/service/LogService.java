package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.TestFrameLog;
import nl.keytech.reservation.model.UserLog;

public interface LogService {
	public List<UserLog> getLastUserLogs(int number);
	
	public List<TestFrameLog> getLastTestFrameLog(int number);
}