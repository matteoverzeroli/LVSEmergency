package it.lvsemergency.accountManagement;

import static org.assertj.core.api.Assertions.assertThat;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

@DataJpaTest
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
public class UserRepositoryTest {
	
	@Autowired
	private UserRepository underTest;
	
	@Test
	void findByUsername() {
			
		String username = "test";
		//given
		User expected = new User(1, username, "Mario", "Rossi","MRARSS80A01C800V","test","Via Nazionale 7","3485556255",'M',"mario@rossi.it",null, UserRole.ADMINISTRATOR,OperativityRole.ACTIVE);
		
		underTest.save(expected);
		
		//when
		User result = underTest.findByUsername(username).get();
		
		//then
		assertThat(expected).isEqualTo(result);
	}
}
