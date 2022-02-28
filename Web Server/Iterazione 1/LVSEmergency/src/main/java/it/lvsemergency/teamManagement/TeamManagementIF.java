package it.lvsemergency.teamManagement;

public interface TeamManagementIF {

	/**
	 * Restistuisce i team presenti nel sistema.
	 */
	public void getTeams();
	
	/**
	 * Restituisce un team specifico.
	 */
	public void getTeam();
	
	/**
	 * Aggiunge un team al sistema.
	 */
	public void addTeam();
	
	/**
	 * Modifica un team già presente nel sistema.
	 */
	public void modifyTeam();
	
	/**
	 * Cancella un team dal sistema.
	 */
	public void deleteTeam();
	
	/**
	 * Imposta il caposquadra di un team del sistema. 
	 */
	public void setForemanTeam();
}
