package org.websparrow.controller;

import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.websparrow.entity.LoginInfo;
import org.websparrow.service.LoginService;
import org.websparrow.service.UserDetailsImpl;

@RestController
public class MyController {
	
	private LoginService loginSerivice = new LoginService();

	@GetMapping("/admin")
	public Object admin() {
		return SecurityContextHolder.getContext().getAuthentication().getPrincipal();
	}

	@GetMapping("/user")
	public Object user() {
		Object userInfo = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
		return userInfo;
		//return "<h2>Welcome User!</h2>";
	}
	
	@GetMapping("/login")
	public LoginInfo login() {
		return loginSerivice.loginInformationRespose((UserDetailsImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
	}
}