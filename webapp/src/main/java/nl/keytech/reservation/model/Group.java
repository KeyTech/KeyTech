package nl.keytech.reservation.model;

import java.util.Calendar;
import java.util.List;
import javax.persistence.*;
import javax.validation.constraints.Future;
import javax.validation.constraints.NotNull;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.hibernate.validator.constraints.NotEmpty;

@Entity
@Table(name = "accessGroup")
public class Group {

	private String groupName;
	private Calendar expirationDate;
	private List<User> users;

	@NotEmpty
	@Id
	@Column(name = "groupName")
	public String getGroupName() {
		return groupName;
	}

	public void setGroupName(String groupName) {
		this.groupName = groupName;
	}

	@Future
	@NotNull
	@Temporal(TemporalType.DATE)
	@Column(name = "expirationDate")
	public Calendar getExpirationDate() {
		return expirationDate;
	}

	public void setExpirationDate(Calendar expirationDate) {
		this.expirationDate = expirationDate;
	}

	@ManyToMany(targetEntity = User.class, fetch = FetchType.EAGER)
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