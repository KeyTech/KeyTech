package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.TestFrameLog;
import nl.keytech.reservation.model.UserLog;
import nl.keytech.reservation.repository.LogRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service("logService")
@Transactional
public class LogServiceImpl implements LogService {
	
	private final LogRepository logRepository;

	public LogServiceImpl(LogRepository logRepository) {
		this.logRepository = logRepository;
	}

	public List<UserLog> getLastUserLogs(int number) {
		return logRepository.getLastUserLogs(number);
	}
	
	public List<TestFrameLog> getLastTestFrameLog(int number) {
		return logRepository.getLastTestFrameLog(number);
	}
	
}
