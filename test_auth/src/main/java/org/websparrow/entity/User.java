package org.websparrow.entity;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "User")
public class User {

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private Integer idUser;
	private String username;
	private String name;
	private String surname;
	private String CF;	
	private String password;
	private String address;
	private Integer cellNumber;
	private Character sex;
	private String email;
	private Integer team;
	private String role;
	private String state;
	
	public Integer getIdUser() {
		return idUser;
	}

	public void setId(Integer idUser) {
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
		return cellNumber;
	}
	
	public void setCellNumber(Integer cellNumber) {
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
	
	public Integer getTeam() {
		return team;
	}
	
	public void setTeam(Integer team) {
		this.team = team;
	}
	
	public String getRole() {
		return role;
	}
	
	public void setRole(String role) {
		this.role = role;
	}
	
	public String getState() {
		return state;
	}
	
	public void setState(String state) {
		this.state = state;
	}
}
