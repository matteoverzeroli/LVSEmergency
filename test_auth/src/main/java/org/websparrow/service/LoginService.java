package org.websparrow.service;

import org.springframework.stereotype.Service;
import org.websparrow.entity.LoginInfo;

@Service
public class LoginService {
	public LoginInfo loginInformationRespose(UserDetailsImpl userInfo) {
		return new LoginInfo(userInfo);
	}
}
