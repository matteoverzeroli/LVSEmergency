package it.lvsemergency.areaInformationManagement.alarm;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface AlarmRepository extends JpaRepository<Alarm, Integer> {

	@Query("select a from Alarm a where a.idArea = ?1 and (a.type = ?2 or a.type = ?3)")
	Alarm findAlarmByIdAreaFogOrFrost(Integer idArea, Sort sort, AlarmType alarmtype, AlarmType alarmtype2, PageRequest limit);

	@Query("select a from Alarm a where a.idArea = ?1 and a.type = ?2")
	Alarm getBadWeatherByIdArea(Integer idArea, Sort sort, AlarmType alarmtype, PageRequest limit);

}
