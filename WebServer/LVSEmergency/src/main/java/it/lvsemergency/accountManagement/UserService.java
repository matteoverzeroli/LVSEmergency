package it.lvsemergency.accountManagement;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UserService implements UserDetailsService {

	@Autowired
	private UserRepository userRepository;

	@Override
	public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {

		Optional<User> user = userRepository.findByUsername(username);
		
		user.orElseThrow(() -> new UsernameNotFoundException(username + " not found."));

		return user.map(UserDetailsImpl::new).get();        
	}
	
	public UserDTO userInformationResponse(UserDetailsImpl userInfo) {
		Optional<User> user = userRepository.findByUsername(userInfo.getUsername());
		
		user.orElseThrow(() -> new UsernameNotFoundException(userInfo.getUsername() + " not found."));

		return user.map(UserDTO::new).get();
	}
	
	

}
