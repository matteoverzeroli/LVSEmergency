package it.lvsemergency.areaInformationManagement.alarm;

import static org.assertj.core.api.Assertions.assertThat;

import java.sql.Date;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import it.lvsemergency.areaInformationManagement.data.AprsData;
import it.lvsemergency.areaInformationManagement.data.AprsDataId;
import it.lvsemergency.areaInformationManagement.data.AprsDataRepository;

@DataJpaTest
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
public class AlarmRepositoryTest {

	@Autowired
	private AprsDataRepository underTest;

	@Test
	void findFirstByIdAreaAndTypeOrTypeOrderByTimeDesc() {
		
		AprsDataId aprsDataId = new AprsDataId("IU2CMQ-13", new Date(2020, 1, 10));
				
		//given
		AprsData expected = new AprsData(aprsDataId, 1.0f, 1.0f, null, null, null, null, null, null, null, null);
		
		underTest.save(expected);
		underTest.findAll();
		
		//when
		AprsData result = underTest.findFirstByAprsDataIdNameOrderByAprsDataIdTimeDesc("IU2CMQ-13");
		
		//then
		assertThat(expected).isEqualTo(result);
		
	}
}
