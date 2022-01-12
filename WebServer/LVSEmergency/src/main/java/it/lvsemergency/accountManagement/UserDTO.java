package it.lvsemergency.accountManagement;

import java.util.Arrays;
import java.util.stream.Collectors;

import org.springframework.security.core.authority.SimpleGrantedAuthority;

import com.fasterxml.jackson.annotation.JsonProperty;

public class UserDTO {
	
	private Integer idUser;
	private String username;
	private String name;
	private String surname;
	private String CF;	
	
	@JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
	private String password;
	private String address;
	private Integer cellnumber;
	private Character sex;
	private String email;
	private Integer team;
	
	
	private UserRole role;
	private String state;
	
	public UserDTO(User user) {
		this.idUser = user.getIdUser();
		this.username = user.getUsername();
		this.password = user.getPassword();
		this.name = user.getName();
		this.surname = user.getSurname();
		this.CF = user.getCF();
		this.password = user.getPassword();
		this.address = user.getAddress();
		this.cellnumber = user.getCellNumber();
		this.sex = user.getSex();
		this.email = user.getEmail();
		this.team = user.getTeam();
		this.role = user.getRole();
		this.state = user.getState();
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
