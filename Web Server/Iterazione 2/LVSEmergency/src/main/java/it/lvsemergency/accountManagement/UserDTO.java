package it.lvsemergency.accountManagement;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;

import com.fasterxml.jackson.annotation.JsonProperty;

public class UserDTO {

	private Integer idUser;

	@NotEmpty
	private String username;

	@NotEmpty
	private String name;

	@NotEmpty
	private String surname;

	@NotEmpty
	private String CF;

	@NotEmpty
	@JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
	private String password;

	@NotEmpty
	private String address;

	@NotEmpty
	private String cellNumber;

	@NotNull
	private Character sex;

	@NotEmpty
	private String email;

	private Integer idTeam;

	@NotNull
	private UserRole role;

	@NotNull
	private OperativityRole state;

	public UserDTO() {

	}

	public UserDTO(User user) {
		this.idUser = user.getIdUser();
		this.username = user.getUsername();
		this.password = user.getPassword();
		this.name = user.getName();
		this.surname = user.getSurname();
		this.CF = user.getCF();
		this.password = user.getPassword();
		this.address = user.getAddress();
		this.cellNumber = user.getCellNumber();
		this.sex = user.getSex();
		this.email = user.getEmail();
		this.idTeam = user.getIdTeam();
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

	public void setTeam(Integer idTeam) {
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
