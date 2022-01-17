package it.lvsemergency.accountManagement;

import java.util.List;

import javax.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.http.HttpStatus;

@RestController
public class UserController {

	private UserService userService;
	
	@Autowired
	public UserController(UserService userService) {
		this.userService = userService;
	}
	
	private User dtoToEntity(UserDTO userDto) {
		var user = new User();
		user.setIdUser(userDto.getIdUser());
		user.setUsername(userDto.getUsername());
		user.setPassword(userDto.getPassword());
		return user;
	}
	
	@GetMapping(path = "/login")
	public UserDTO login() {
		return userService.userInformationResponse((UserDetailsImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
	}
	
	@GetMapping(path = "/users")
	public List<UserDTO>  getUsers() {
		return userService.getUsers();
	}
	
	@GetMapping(path = "/users/{idUser}")
	public UserDTO getUser(@PathVariable Integer idUser) {
		return userService.getUser(idUser);
	}
	
	@GetMapping(path = "/users/team/{team}")
	public List<UserDTO> getUsersInTeam(@PathVariable Integer team) {
		return userService.getUsersInTeam(team);
	}
	
	@DeleteMapping("/users/{idUser}")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public void deleteEmployee(@PathVariable Integer idUser) {
		userService.deleteUser(idUser);
	}
	
	@PutMapping(path = "/users")
	public UserDTO modifyUser(@Valid @RequestBody UserDTO userDto) {
		return userService.modifyUser(userDto);
	}
	
	@PostMapping(path = "/users")
	@ResponseStatus(HttpStatus.CREATED)
	public UserDTO addUser(@Valid @RequestBody UserDTO userDto) {
		return userService.addUser(userDto);
	}
	
}
