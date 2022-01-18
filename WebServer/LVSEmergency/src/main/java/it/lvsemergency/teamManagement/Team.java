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

import com.fasterxml.jackson.annotation.JsonIgnore;

import it.lvsemergency.accountManagement.User;

@Table(name = "Team")
@Entity
public class Team {
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idTeam;

	private String teamName;
	private int idForeman;
	
	@OneToMany(targetEntity=User.class, mappedBy="team", fetch = FetchType.LAZY)    
	private List<User> users = new LinkedList<User>();

	Team () {
		
	}
	
	public Team(Integer idTeam, String teamName, int idForeman) {
		this.idTeam = idTeam;
		this.teamName = teamName;
		this.idForeman = idForeman;
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

	public int getIdForeman() {
		return idForeman;
	}

	public void setIdForeman(int idForeman) {
		this.idForeman = idForeman;
	}
	
	public List<User> getUsers() {
		return users;
	}

	public void setUsers(List<User> users) {
		this.users = users;
	}
	
}
