package it.lvsemergency.areaInformationManagement.data;

import static org.assertj.core.api.Assertions.assertThat;

import java.sql.Timestamp;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

@DataJpaTest
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
public class AprsDataRepositoryTest {

	@Autowired
	private AprsDataRepository underTest;

	@Test
	void findFirstByAprsDataIdNameOrderByAprsDataIdTimeDesc() {
		
		Timestamp now = new Timestamp(System.currentTimeMillis());
		now.setNanos(0);
		
		AprsDataId aprsDataId = new AprsDataId("IU2CMQ-13", now);
				
		//given
		AprsData expected = new AprsData(aprsDataId, 2.8f, 1025.7f, 81, 135f, 0f, 0f, 0f, 1.8f, 2.9f, null);
		
		underTest.save(expected);
		underTest.findAll();
		
		//when
		AprsData result = underTest.findFirstByAprsDataIdNameOrderByAprsDataIdTimeDesc("IU2CMQ-13");
		
		//then
		assertThat(expected).isEqualTo(result);
		
	}
}
