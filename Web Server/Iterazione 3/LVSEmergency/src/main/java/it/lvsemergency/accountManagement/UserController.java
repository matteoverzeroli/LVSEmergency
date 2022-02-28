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
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import it.lvsemergency.accountManagement.position.Position;
import it.lvsemergency.accountManagement.position.PositionDTO;

import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.http.HttpStatus;

@RestController
public class UserController {

	private AccountManagementIF userService;

	@Autowired
	public UserController(UserService userService) {
		this.userService = userService;
	}

	@GetMapping(path = "/login")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public UserDTO login() {
		return userService.login(
				(UserDetailsImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
	}

	@GetMapping(path = "/users")
	public List<UserDTO> getUsers() {
		return userService.getUsers();
	}

	@GetMapping(path = "/users/{idUser}")
	public UserDTO getUser(@PathVariable Integer idUser) {
		return userService.getUser(idUser);
	}

	@DeleteMapping(path = "/users/{idUser}")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public void deleteUser(@PathVariable Integer idUser) {
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
	
	@GetMapping(path = "/users/{idUser}/position")
	public PositionDTO getUserPosition(@PathVariable Integer idUser) {
		return userService.getUserPosition(idUser);
	}

	@PostMapping(path = "/users/{idUser}/position")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public String setUserPosition(@Valid @RequestBody Position position, @PathVariable Integer idUser) {
		userService.setUserPosition(position, idUser);
		return "Position set correctly!";
	}

}
