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
public class AreaService implements AreaInformationManagementIF{

	@Autowired
	private AreaRepository areaRepository;

	@Autowired
	private AprsDataRepository aprsDataRepository;

	@Autowired
	private AlarmRepository alarmRepository;

	/**
	 * Restistuisce le aree presenti nel sistema.
	 * 
	 * @return List<Area> lista delle aree presenti.
	 */
	@Override
	public List<Area> getAreas() {
		return areaRepository.findAll();
	}

	/**
	 * Restistuisce una specifica area presente nel sistema.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere informazioni.
	 * @return Area richiesta.
	 */
	@Override
	public Area getArea(Integer idArea) {
		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		return area.get();
	}

	/**
	 * Restituisce tutti i dati APRS presenti nel sistema.
	 * 
	 * @return List<AprsData> lista di dati presenti nel sistema.
	 */
	@Override
	public List<AprsData> getAprsDatas() {
		return aprsDataRepository.findAll();
	}

	/**
	 * Restituisce l'ultimo dato APRS di una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere il dato APRS.
	 * @return AprsData Dati APRS dell'area.
	 */
	@Override
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

	/**
	 * Restistuisce l'ultimo allarme presente relativo al maltempo per una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere l'allarme.
	 * @return Alarm Ultimo allarme disponibile.
	 */
	@Override
	public Alarm getFogOrFrostAlarmByIdArea(Integer idArea) {

		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		Sort sort = Sort.by(Sort.Direction.DESC, "time");
		Alarm alarm = alarmRepository.findAlarmByIdAreaFogOrFrost(idArea, sort, AlarmType.FROST, AlarmType.FOG, PageRequest.of(0, 1));

		return alarm;
	}

	/**
	 * Restistuisce l'ultimo allarme presente relativo a nebbia o brina per una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere l'allarme.
	 * @return Alarm Ultimo allarme disponibile.
	 */
	@Override
	public Alarm getBadWeatherByIdArea(Integer idArea) {

		Optional<Area> area = areaRepository.findById(idArea);

		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No area found!");

		Sort sort = Sort.by(Sort.Direction.DESC, "time");
		
		Alarm alarm = alarmRepository.getBadWeatherByIdArea(idArea, sort, AlarmType.BW, PageRequest.of(0, 1));

		return alarm;
	}

}
