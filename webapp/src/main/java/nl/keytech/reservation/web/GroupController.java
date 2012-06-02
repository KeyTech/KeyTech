package nl.keytech.reservation.web;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.validation.Valid;
import nl.keytech.reservation.model.Group;
import nl.keytech.reservation.service.GroupService;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.validation.MapBindingResult;
import org.springframework.validation.Validator;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("group")
public class GroupController {
	
	private final GroupService groupService;
	private final Validator validator;

	public GroupController(GroupService groupService, Validator validator) {
		this.groupService = groupService;
		this.validator = validator;
	}
	
	@RequestMapping("searchAjax")
	public @ResponseBody List<Group> searchAjax(@RequestParam("query") String query) {
		return groupService.search(query);
	}
	
	@RequestMapping("save")
	public @ResponseBody Map save(@RequestBody Group group) {
		Map<String, Object> result = new HashMap<String, Object>();
		MapBindingResult errors = new MapBindingResult(new HashMap<String, String>(), group.getClass().getName());
		
		validator.validate(group, errors);
		
		if(errors.hasErrors()) {
			result.put("success", false);
			result.put("message", errors.getAllErrors().get(0).getDefaultMessage());
			return result;
		}
		
		groupService.save(group);

		return result;
	}
	
	@RequestMapping("get")
	public @ResponseBody Group get(@RequestParam("groupName") String groupName) {
		return groupService.get(groupName);
	}	
}
