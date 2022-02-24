package it.lvsemergency.accountManagement;

import java.util.List;

public interface AccountManagementIF {
	
	/**
	 * Restituisce le informazioni dell'utente che sta eseguendo
	 * il login.
	 * 
	 * @param userInfo username e password dell'utente che sta eseguendo il login.
	 * @return UserDTO dell'utente che sta eseguendo il login.
	 */
	public UserDTO login(UserDetailsImpl userInfo);
	
	/**
	 * Restituisce tutti gli utenti registrati.
	 * 
	 * @return List<UserDTO> informazioni degli utenti.
	 */
	public List<UserDTO> getUsers();
	
	/**
	 * Restituisce un particolare utente.
	 * 
	 * @param idUser id dell'utente richiesto.
	 * @return UserDTO dell'utente avente idUser.
	 */
	public UserDTO getUser(Integer idUser);
	
	/**
	 * Inserisce un nuovo utente nel sistema.
	 * 
	 * @param userDto Informazioni dell'utente da inserire.
	 * @return UserDTO dell'utente inserito.
	 */
	public UserDTO addUser(UserDTO userDto);
	
	/**
	 * Modifica un utente giÃ  presente nel sistema.
	 * 
	 * @param userDto Nuove informazioni dell'utente da modificare.
	 * @return UserDTO dell'utente dopo le modifiche.
	 */
	public UserDTO modifyUser(UserDTO userDto);
	
	/**
	 * Cancella un utente dal sistema.
	 * 
	 * @param idUser id dell'utente da cancellare.
	 */
	public void deleteUser(Integer idUser);
}
