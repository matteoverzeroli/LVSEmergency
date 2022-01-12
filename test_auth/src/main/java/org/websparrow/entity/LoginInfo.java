package org.websparrow.entity;

import org.websparrow.service.UserDetailsImpl;

public class LoginInfo {
	
	private Integer iduser;
	private String role;

	public LoginInfo(UserDetailsImpl userInfo) {
		this.iduser = userInfo.getiduser();
		this.role = userInfo.getRole();
	}
	
	public Integer getiduser() {
		return iduser;
	}
	
	public String getRole() {
		return role;
	}
}
