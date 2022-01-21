package it.lvsemergency.teamManagement;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;

public class TeamDTO {
	
	private Integer idTeam;

	@NotNull
	private String teamName;
	
	@NotNull
	private Integer idForeman;
	
	@NotNull
	private Integer idArea;
	
	public TeamDTO() {
		
	}
	
	public TeamDTO(Team team) {
		this.teamName = team.getTeamName();
		this.idForeman = team.getIdForeman();
		this.idArea = team.getArea().getIdArea();
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
}
