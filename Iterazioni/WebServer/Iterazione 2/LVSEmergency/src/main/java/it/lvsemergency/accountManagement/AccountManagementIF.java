package it.lvsemergency.accountManagement;

import java.util.List;

public interface AccountManagementIF {
	
	public UserDTO login(UserDetailsImpl userInfo);
	
	public List<UserDTO> getUsers();
	
	public UserDTO getUser(Integer idUser);
	
	public UserDTO addUser(UserDTO userDto);
	
	public UserDTO modifyUser(UserDTO userDto);
	
	public void deleteUser(Integer idUser);
}
