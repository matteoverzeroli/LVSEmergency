package it.lvsemergency.teamManagement;

import java.util.List;

public interface TeamManagementIF {
	
	/**
	 * Restistuisce tutti i team presenti nel sistema.
	 * 
	 * @return List<Team> Team presenti nel sistema.
	 */
	public List<Team> getTeams();
	
	/**
	 * Inserisce un nuovo team nel sistema.
	 * 
	 * @param teamDto Informazioni sul nuovo team da inserire. 
	 */
	public void addTeam(TeamDTO teamDto);
	
	/**
	 * Restituisce un particolare Team.
	 * 
	 * @param idTeam id del Team di interesse.
	 * @return Team Informazioni riguardanti il team richiesto.
	 */
	public Team getTeam(Integer idTeam);
	
	/**
	 * Cancella un team dal sistema.
	 * 
	 * @param idTeam id del team che si desidera cancellare. 
	 */
	public void deleteTeam(Integer idTeam);
	
	/**
	 * Imposta il caposquadra di un team.
	 * 
	 * @param idTeam id del team di cui deve essere importato il caposquadra.
	 * @param idForeman id del caposquadra da assegnare al team. 
	 */
	public void setForemanTeam(Integer idTeam, Integer idForeman);

}
