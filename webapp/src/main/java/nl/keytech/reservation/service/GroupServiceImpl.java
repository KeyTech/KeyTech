package nl.keytech.reservation.service;

import java.util.List;
import nl.keytech.reservation.model.Group;
import nl.keytech.reservation.repository.GroupRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

@Service("groupService")
@Transactional
public class GroupServiceImpl implements GroupService {

	private final GroupRepository groupRepository;

	public GroupServiceImpl(GroupRepository groupRepository) {
		this.groupRepository = groupRepository;
	}

	public List<Group> getAll() {
		return groupRepository.getAll();
	}

	public Group get(String name) {
		return groupRepository.get(name);
	}
}