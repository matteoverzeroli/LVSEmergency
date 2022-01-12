package org.websparrow.service;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.websparrow.entity.Role;
import org.websparrow.entity.State;
import org.websparrow.entity.User;

public class UserDetailsImpl implements UserDetails {

	private Integer iduser;
	private String username;
	private String name;
	private String surname;
	private String CF;	
	private String password;
	private String address;
	private Integer cellnumber;
	private Character sex;
	private String email;
	private Integer team;
	private String role;
	private String state;
	private List<GrantedAuthority> authorities;

	public UserDetailsImpl(User user) {
		this.iduser = user.getiduser();
		this.username = user.getUsername();
		this.password = user.getPassword();
		this.name = user.getName();
		this.surname = user.getSurname();
		this.CF = user.getCF();
		this.password = user.getPassword();
		this.address = user.getAddress();
		this.cellnumber = user.getCellNumber();
		this.sex = user.getSex();
		this.email = user.getEmail();
		this.team = user.getTeam();
		this.role = user.getRole();
		this.state = user.getState();
		
		
		this.authorities = Arrays.stream(user.getRole().toString().split(","))
				.map(SimpleGrantedAuthority::new)
				.collect(Collectors.toList());
	}

	@Override
	public Collection<? extends GrantedAuthority> getAuthorities() {
		return authorities;
	}

	@Override
	public String getPassword() {
		return password;
	}

	@Override
	public String getUsername() {
		return username;
	}

	@Override
	public boolean isAccountNonExpired() {
		return true;
	}

	@Override
	public boolean isAccountNonLocked() {
		return true;
	}

	@Override
	public boolean isCredentialsNonExpired() {
		return true;
	}

	@Override
	public boolean isEnabled() {
		return true;
	}
	
	public Integer getiduser() {
		return iduser;
	}
	
	public String getRole() {
		return role;
	}

}
