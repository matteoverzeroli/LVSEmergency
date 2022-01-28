package it.lvsemergency.areaInformationManagement;

import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

import it.lvsemergency.areaInformationManagement.alarm.Alarm;
import it.lvsemergency.areaInformationManagement.alarm.AlarmRepository;
import it.lvsemergency.areaInformationManagement.alarm.AlarmType;
import it.lvsemergency.areaInformationManagement.data.AprsData;
import it.lvsemergency.areaInformationManagement.data.AprsDataRepository;

@Service
public class AreaService {

	@Autowired
	private AreaRepository areaRepository;

	@Autowired
	private AprsDataRepository aprsDataRepository;

	@Autowired
	private AlarmRepository alarmRepository;

	public List<Area> getAreas() {
		return areaRepository.findAll();
	}

	public Area getArea(Integer idArea) {
		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		return area.get();
	}

	public List<AprsData> getAprsDatas() {
		return aprsDataRepository.findAll();
	}

	public AprsData getAprsDataByIdArea(Integer idArea) {

		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		String nameAprsStation = area.get().getNameAprsStation();

		if (nameAprsStation.isEmpty())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND,
					"No aprs station found with area id: " + idArea + "!");

		return aprsDataRepository.findFirstByAprsDataIdNameOrderByAprsDataIdTimeDesc(nameAprsStation);
	}

	public Alarm getFogOrFrostAlarmByIdArea(Integer idArea) {

		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		Sort sort = Sort.by(Sort.Direction.DESC, "time");
		Alarm alarm = alarmRepository.findAlarmByIdAreaFogOrFrost(idArea, sort, AlarmType.FROST, AlarmType.FOG, PageRequest.of(0, 1));

		return alarm;
	}

	public Alarm getBadWeatherByIdArea(Integer idArea) {

		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		Sort sort = Sort.by(Sort.Direction.DESC, "time");
		
		Alarm alarm = alarmRepository.getBadWeatherByIdArea(idArea, sort, AlarmType.BW, PageRequest.of(0, 1));

		return alarm;
	}

}
