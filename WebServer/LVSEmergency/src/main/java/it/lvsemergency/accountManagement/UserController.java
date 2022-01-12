package it.lvsemergency.accountManagement;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UserController {

	private UserService userService;
	
	@Autowired
	public UserController(UserService userService) {
		this.userService = userService;
	}
	
	@GetMapping("/login")
	public UserDTO login() {
		return userService.userInformationResponse((UserDetailsImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
	}
	
}
