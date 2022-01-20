package it.lvsemergency.teamManagement;

import java.util.LinkedList;
import java.util.List;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;

import it.lvsemergency.accountManagement.User;

@Table(name = "Team")
@Entity
public class Team {
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idTeam;

	private String teamName;
	private Integer idForeman;
	private Integer idArea;
	
	@OneToMany(targetEntity=User.class, mappedBy="idTeam", fetch = FetchType.LAZY)    
	private List<User> users = new LinkedList<User>();

	Team () {
		
	}
	
	public Team(Integer idTeam, String teamName, Integer idForeman, Integer idArea) {
		this.idTeam = idTeam;
		this.teamName = teamName;
		this.idForeman = idForeman;
		this.idArea = idArea;
		this.users = new LinkedList<User>();
	}
	
	public Integer getIdTeam() {
		return idTeam;
	}

	public void setIdTeam(Integer idTeam) {
		this.idTeam = idTeam;
	}

	public String getTeamName() {
		return teamName;
	}

	public void setTeamName(String teamName) {
		this.teamName = teamName;
	}

	public Integer getIdForeman() {
		return idForeman;
	}

	public void setIdForeman(Integer idForeman) {
		this.idForeman = idForeman;
	}
	
	public Integer getIdArea() {
		return idArea;
	}
	
	public void setIdArea(Integer idArea) {
		this.idArea = idArea;
	}
	
	public List<User> getUsers() {
		return users;
	}

	public void setUsers(List<User> users) {
		this.users = users;
	}
	
}
