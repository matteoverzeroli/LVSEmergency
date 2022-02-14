package it.lvsemergency.areaInformationManagement.data;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface AprsDataRepository extends JpaRepository<AprsData, AprsDataId>{
	
	AprsData findFirstByAprsDataIdNameOrderByAprsDataIdTimeDesc(String name);

}
