package it.lvsemergency.accountManagement;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.data.domain.Sort;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

@Service
public class UserService implements AccountManagementIF, UserDetailsService {

	@Autowired
	private UserRepository userRepository;

	@Autowired
	private ModelMapper modelMapper;

	@Override
	public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {

		Optional<User> user = userRepository.findByUsername(username);

		user.orElseThrow(() -> new UsernameNotFoundException(username + " not found."));

		return user.map(UserDetailsImpl::new).get();
	}

	@Override
	public UserDTO login(UserDetailsImpl userInfo) {
		Optional<User> user = userRepository.findByUsername(userInfo.getUsername());

		user.orElseThrow(() -> new UsernameNotFoundException(userInfo.getUsername() + " not found."));

		return user.map(UserDTO::new).get();
	}

	@Override
	public List<UserDTO> getUsers() {
		return userRepository.findAll(Sort.by(Sort.Direction.ASC, "idUser")).stream()
				.map(user -> modelMapper.map(user, UserDTO.class)).collect(Collectors.toList());
	}

	@Override
	public UserDTO getUser(Integer idUser) {
		Optional<User> user = userRepository.findById(idUser);

		if (!user.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "User doesn't exist");

		return modelMapper.map(user.get(), UserDTO.class);
	}

	@Override
	public UserDTO addUser(UserDTO userDto) {
		Optional<User> user = userRepository.findByUsername(userDto.getUsername());

		if (!user.isEmpty())
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "User already exists");
		
		User newUser = modelMapper.map(userDto, User.class);
		newUser = userRepository.save(newUser);
		
		return modelMapper.map(newUser, UserDTO.class);
	}

	@Override
	public UserDTO modifyUser(UserDTO userDto) {
		Optional<User> userToModify = userRepository.findByUsername(userDto.getUsername());

		if (!userToModify.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No user to delete");

		User user = userToModify.get();

		modelMapper.map(userDto, user);

		return modelMapper.map(userRepository.save(user), UserDTO.class);
	}

	@Override
	public void deleteUser(Integer idUser) {
		Optional<User> userToDelete = userRepository.findById(idUser);

		if (!userToDelete.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No user to delete");

		userRepository.delete(userToDelete.get());
	}

}
