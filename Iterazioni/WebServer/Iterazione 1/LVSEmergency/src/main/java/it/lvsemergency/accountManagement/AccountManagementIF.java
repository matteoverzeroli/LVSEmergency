package it.lvsemergency.accountManagement;

public interface AccountManagementIF {
	
	/**
	 * Funzione per eseguire il login dell'utente.
	 */
	public void login();
	
	/**
	 * Funzione che restituisce gli utenti presenti nel sistema.
	 */
	public void getUsers();
	
	/**
	 * Funzione che restituisce un particolare utente presente nel sistema.
	 */
	public void getUser();
	
	/**
	 * Funzione che cancella un utente presente nel sistema.
	 */
	public void deleteUser();
	
	/**
	 * Funzione per inserire un nuovo utente nel sistema.
	 */
	public void addUser();
	
	/**
	 * Funzione per modificare le proprietà di un utente.
	 */
	public void modifyUser();
	
	/**
	 * Funzione per l'inserimento delle disponibilità dell'utente.
	 */
	public void inertAvailability();
	
	/**
	 * Funzione per modificare le disponibilità dell'utente.
	 */
	public void modifyAvailability();
	
	/**
	 * Funzione per eliminare le disponibilità dell'utente.
	 */
	public void deleteAvailability();
	
	/**
	 * Funzione per impostare lo stato di operatività di un utente,
	 * "Operativo" o "Non Operativo".
	 */
	public void setOperativity();
	
	/**
	 * Funzione che restituisce la posizione di un utente
	 */
	
	public void getUserPosition();
	
	/**
	 * Funzione che permette di inserire la posizione di un utente
	 */
	
	public void setUserPosition();
}
