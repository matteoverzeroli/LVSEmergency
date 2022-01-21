package it.lvsemergency.teamManagement;

import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.Table;

import it.lvsemergency.accountManagement.User;
import it.lvsemergency.areaInformationManagement.Area;

@Table(name = "team")
@Entity
public class Team {
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idTeam;

	private String teamName;
	private Integer idForeman;

	@OneToMany(targetEntity = User.class, mappedBy = "idTeam", fetch = FetchType.LAZY)
	private List<User> users;
	
	@OneToOne
    @JoinColumn(name = "idArea", referencedColumnName = "idArea")
	private Area area;
	
	Team() {

	}

	public Team(Integer idTeam, String teamName, Integer idForeman, Area area) {
		super();
		this.idTeam = idTeam;
		this.teamName = teamName;
		this.idForeman = idForeman;
		this.area = area;
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

	public List<User> getUsers() {
		return users;
	}

	public void setUsers(List<User> users) {
		this.users = users;
	}
	
	public Area getArea() {
		return area;
	}
	
	public void setArea(Area area) {
		this.area = area;
	}
}
