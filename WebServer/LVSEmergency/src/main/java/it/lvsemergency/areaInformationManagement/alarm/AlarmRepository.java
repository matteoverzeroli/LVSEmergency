package it.lvsemergency.areaInformationManagement.alarm;

import org.springframework.data.jpa.repository.JpaRepository;

public interface AlarmRepository extends JpaRepository<Alarm, Integer>{

	Alarm findFirstByIdAreaAndTypeOrTypeOrderByTimeDesc(Integer idArea, AlarmType alarmType, AlarmType alarmType2);

}
