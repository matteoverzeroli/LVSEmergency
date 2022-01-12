package it.lvsemergency.accountManagement;

import javax.persistence.Column;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;


@Table(name = "User")
@Entity
public class User {

	@Id
	@Column(name = "idUser")
	Integer idUser;
	private String username;
	private String name;
	private String surname;
	private String CF;	
	private String password;
	private String address;
	private Integer cellnumber;
	private Character sex;
	private String email;
	private Integer team;
	
	@Enumerated(EnumType.STRING)
	private UserRole role;
	
	private String state;
	
	User() {
	}

	public User(Integer iduser, String username, String name, 
			String surname, String CF, String password, 
			String address, Integer cellnumber, Character sex, 
			String email, Integer team, UserRole role, String state) {
		super();
		
		this.idUser = iduser;
		this.username = username;
		this.name = name;
		this.surname = surname;
		this.CF = CF;
		this.password = password;
		this.address = address;
		this.cellnumber = cellnumber;
		this.sex = sex;
		this.email = email;
		this.team = team;
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
	
	public Integer getCellNumber() {
		return cellnumber;
	}
	
	public void setCellNumber(Integer cellNumber) {
		this.cellnumber = cellNumber;
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
	
	public Integer getTeam() {
		return team;
	}
	
	public void setTeam(Integer team) {
		this.team = team;
	}
	
	public UserRole getRole() {
		return role;
	}
	
	public void setRole(UserRole role) {
		this.role = role;
	}
	
	public String getState() {
		return state;
	}
	
	public void setState(String state) {
		this.state = state;
	}
}