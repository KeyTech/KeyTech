package nl.keytech.reservation.web;

import java.util.List;
import nl.keytech.reservation.model.Room;
import nl.keytech.reservation.service.RoomService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("room")
public class RoomController {
	
	private final RoomService roomService;

	public RoomController(RoomService roomService) {
		this.roomService = roomService;
	}
	
	@RequestMapping("searchAjax")
	public @ResponseBody List<Room> searchAjax(@RequestParam("query") String query) {
		return roomService.search(query);
	}
}
