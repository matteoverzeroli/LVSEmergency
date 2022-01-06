package org.websparrow.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MyController {

	@GetMapping("/admin")
	public String admin() {
		return "<h2>Welcome Admin!</h2>";
	}

	@GetMapping("/user")
	public String user() {
		return "<h2>Welcome User!</h2>";
	}

	@GetMapping("/all")
	public String all() {
		return "<h2>Hello Everyone!</h2>";
	}
}