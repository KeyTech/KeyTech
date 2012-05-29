package nl.keytech.reservation.model;

import java.util.List;
import javax.persistence.*;

@Entity
@Table(name = "accessGroup")
public class Group {

	private String groupName;
	private List<User> users;

	@Id
	@Column(name = "groupName")
	public String getGroupName() {
		return groupName;
	}

	public void setGroupName(String groupName) {
		this.groupName = groupName;
	}

	@ManyToMany(targetEntity = User.class)
	@JoinTable(
			name = "userAccessGroup",
			uniqueConstraints= @UniqueConstraint(columnNames={ "groupName", "userIdentifier" }),
			joinColumns = @JoinColumn(name = "groupName"),
			inverseJoinColumns = @JoinColumn(name = "userIdentifier")
	)
	public List<User> getUsers() {
		return users;
	}

	public void setUsers(List<User> users) {
		this.users = users;
	}
}