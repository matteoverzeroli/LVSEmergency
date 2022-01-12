package it.lvsemergency;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.security.config.core.GrantedAuthorityDefaults;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class LvsEmergencyApplication {

	
	@Bean
	GrantedAuthorityDefaults grantedAuthorityDefaults() {
	    return new GrantedAuthorityDefaults(""); // Remove the ROLE_ prefix
	}
	
	public static void main(String[] args) {
		SpringApplication.run(LvsEmergencyApplication.class, args);
	}
	
	@GetMapping
	public String helloworld() {
		return "Hello";
	}

}
