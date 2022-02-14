package it.lvsemergency.teamManagement;

import java.util.List;

public interface TeamManagementIF {
	
	public List<Team> getTeams();
	
	public void addTeam(TeamDTO teamDto);
	
	public Team getTeam(Integer idTeam);
	
	public void deleteTeam(Integer idTeam);
	
	public void setForemanTeam(Integer idTeam, Integer idForeman);

}
