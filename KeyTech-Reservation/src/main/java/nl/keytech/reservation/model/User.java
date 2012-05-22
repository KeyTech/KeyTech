package nl.keytech.reservation.model;

import java.io.Serializable;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "user")
public class User implements Serializable {
	
	private int userIdentifier;
	private short pincode;
	private String firstname;
	private String lastname;

	@Id
	@Column(name = "userIdentifier")
	public int getUserIdentifier() {
		return userIdentifier;
	}

	public void setUserIdentifier(int userIdentifier) {
		this.userIdentifier = userIdentifier;
	}

	@Column(name = "firstname", length = 40)
	public String getFirstname() {
		return firstname;
	}

	public void setFirstname(String firstname) {
		this.firstname = firstname;
	}

	@Column(name = "lastname", length = 40)
	public String getLastname() {
		return lastname;
	}

	public void setLastname(String lastname) {
		this.lastname = lastname;
	}

	@Column(name = "pincode")
	public short getPincode() {
		return pincode;
	}

	public void setPincode(short pincode) {
		this.pincode = pincode;
	}
}
