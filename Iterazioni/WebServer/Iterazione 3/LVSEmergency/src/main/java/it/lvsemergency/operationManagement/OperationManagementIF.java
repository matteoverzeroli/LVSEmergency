package it.lvsemergency.operationManagement;

public interface OperationManagementIF {

	/**
	 * Restituisce informazioni su un intervento programmato.
	 */
	public void getScheduledOperationInformation();
	
	/**
	 * Restituisce informazioni su un intervento di emergenza.
	 */
	public void getEmergencyOperationInformation();
	
	/**
	 * Inserisce delle informazioni aggiuntive riguardo il report di 
	 * un intervento programmato. Queste informazioni vengono fornite
	 * dai volontari e dai caposquadra che partecipano all'intervento.
	 */
	public void insertScheduledOperationInformationReport();
	
	/**
	 * Inserisce delle informazioni aggiuntive riguardo il report di 
	 * un intervento di emergenza. Queste informazioni vengono fornite
	 * dai volontari e dai caposquadra che partecipano all'intervento.
	 */
	public void insertEmergencyOperationInformationForReport();
	
	/**
	 * Visualizza la posizione RT degli utenti della squadra durante l'intervento.
	 */
	public void visualizeRTPosition();
	
	/**
	 * Crea un intervento programmato.
	 */
	public void createScheduledOperation();
	
	/**
	 * Modifica un intervento programmato.
	 */
	public void modifyScheduledOperation();
	
	/**
	 * Elimina un intervento programmato.
	 */
	public void deleteScheduledOperation();
	
	/**
	 * Crea un intervento di emergenza.
	 */
	public void createEmergencyOperation();
	
	/**
	 * Modifica un intervento di emergenza.
	 */
	public void modifyEmergencyOperation();
	
	/**
	 * Elimina un intervento di emergenza.
	 */
	public void deleteEmergencyOperation();
	
	/**
	 * Restituisce il report di un intervento programmato.
	 */
	public void getScheduledOperationReport();
	
	/**
	 * Modifica il report di un intervento programmato.
	 */
	public void modifyScheduledOperationReport();
	
	/**
	 * Restistuisce il report di un intervento di emergenza.
	 */
	public void getEmergencyOperationReport();
	
	/**
	 * Modifica il report di un intervento di emergenza.
	 */
	public void modifyEmergencyOperationReport();
}
