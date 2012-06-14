package nl.keytech.reservation.web;

import java.util.List;
import nl.keytech.reservation.model.TestFrameLog;
import nl.keytech.reservation.model.UserLog;
import nl.keytech.reservation.service.LogService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@RequestMapping("log")
@Controller
public class LogController {

	private final LogService logService;

	public LogController(LogService logService) {
		this.logService = logService;
	}

	@RequestMapping("")
	public String log() {
		return "log/index";
	}
	
	@RequestMapping("userLog")
	public @ResponseBody List<UserLog> userLogs() {
		return logService.getLastUserLogs(10);
	}
	
	@RequestMapping("testFrameLog")
	public @ResponseBody List<TestFrameLog> testFrameLogs() {
		return logService.getLastTestFrameLog(10);
	}
}
