package it.lvsemergency.config;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.password.NoOpPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import it.lvsemergency.accountManagement.UserService;

@SuppressWarnings("deprecation")
@EnableWebSecurity
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {

	@Autowired
	private UserService userService;

	@Override
	protected void configure(AuthenticationManagerBuilder auth) throws Exception {
		auth.userDetailsService(userService);
	}

	@Override
	protected void configure(HttpSecurity http) throws Exception {
		http.authorizeRequests()
//          .antMatchers(HttpMethod.GET, "/login").hasRole(UserRole.ADMINISTRATOR.toString(), 
//        		  										 UserRole.FOREMAN.toString(),
//        		  										 UserRole.VOLUNTEER.toString())
//          .antMatchers(HttpMethod.GET, "/users").hasRole(UserRole.ADMINISTRATOR.toString())
//          .antMatchers(HttpMethod.POST, "/users").hasRole(UserRole.ADMINISTRATOR.toString())
//          .antMatchers(HttpMethod.DELETE, "/users").hasRole(UserRole.ADMINISTRATOR.toString())
//		  .antMatchers(HttpMethod.PUT, "/users").hasAnyRole()
				.anyRequest().authenticated().and().csrf().disable().sessionManagement()
				.sessionCreationPolicy(SessionCreationPolicy.STATELESS).and().httpBasic();
	}

	@Bean
	public PasswordEncoder getPasswordEncoder() {
		return NoOpPasswordEncoder.getInstance();
	}
}
