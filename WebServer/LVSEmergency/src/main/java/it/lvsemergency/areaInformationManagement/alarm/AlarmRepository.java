package it.lvsemergency.areaInformationManagement.alarm;

import java.util.List;

import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
public interface AlarmRepository extends JpaRepository<Alarm, Integer>{

	@Query("select a from Alarm a where a.idArea = ?1 and (a.type = ?2 or a.type = ?3)")
	List<Alarm> findAlarmByIdAreaFogOrFrost(Integer idArea, Sort sort, AlarmType alarmtype, AlarmType alarmtype2);
	

}
