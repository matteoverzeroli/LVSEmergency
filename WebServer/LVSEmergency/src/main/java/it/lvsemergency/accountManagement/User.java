package it.lvsemergency.accountManagement;

import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

import com.fasterxml.jackson.annotation.JsonProperty;


@Table(name = "User")
@Entity
public class User {
	
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idUser;
	
	private String username;
	private String name;
	private String surname;
	private String CF;	
	
	@JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
	private String password;
	private String address;
	private String cellNumber;
	private Character sex;
	private String email;
	private Integer idTeam;
	
	@Enumerated(EnumType.STRING)
	private UserRole role;
	
	@Enumerated(EnumType.STRING)
	private OperativityRole state;
	
	User() {
	}

	public User(Integer iduser, String username, String name, 
			String surname, String CF, String password, 
			String address, String cellNumber, Character sex, 
			String email, Integer idTeam, UserRole role, 
			OperativityRole state) {
		super();
		
		this.idUser = iduser;
		this.username = username;
		this.name = name;
		this.surname = surname;
		this.CF = CF;
		this.password = password;
		this.address = address;
		this.cellNumber = cellNumber;
		this.sex = sex;
		this.email = email;
		this.idTeam = idTeam;
		this.role = role;
		this.state = state;
	}
	
	
	public Integer getIdUser() {
		return idUser;
	}

	public void setIdUser(Integer idUser) {
		this.idUser = idUser;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public String getSurname() {
		return surname;
	}
	
	public void setSurname(String surname) {
		this.surname = surname;
	}
	
	public String getCF() {
		return CF;
	}
	public void setCF(String cF) {
		CF = cF;
	}
		
	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getAddress() {
		return address;
	}
	
	public void setAddress(String address) {
		this.address = address;
	}
	
	public String getCellNumber() {
		return cellNumber;
	}
	
	public void setCellNumber(String cellNumber) {
		this.cellNumber = cellNumber;
	}
	
	public Character getSex() {
		return sex;
	}
	
	public void setSex(Character sex) {
		this.sex = sex;
	}
	
	public String getEmail() {
		return email;
	}
	
	public void setEmail(String email) {
		this.email = email;
	}
	
	public Integer getIdTeam() {
		return idTeam;
	}
	
	public void setIdTeam(Integer idTeam) {
		this.idTeam = idTeam;
	}
	
	public UserRole getRole() {
		return role;
	}
	
	public void setRole(UserRole role) {
		this.role = role;
	}
	
	public OperativityRole getState() {
		return state;
	}
	
	public void setState(OperativityRole state) {
		this.state = state;
	}
}