package nl.keytech.reservation.web;

import java.util.List;
import nl.keytech.reservation.model.Group;
import nl.keytech.reservation.service.GroupService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("group")
public class GroupController {
	
	private final GroupService groupService;

	public GroupController(GroupService groupService) {
		this.groupService = groupService;
	}
	
	@RequestMapping("searchAjax")
	public @ResponseBody List<Group> searchAjax(@RequestParam("query") String query) {
		return groupService.search(query);
	}
}
