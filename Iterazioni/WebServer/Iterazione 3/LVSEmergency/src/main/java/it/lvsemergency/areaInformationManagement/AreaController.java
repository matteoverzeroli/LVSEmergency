package it.lvsemergency.areaInformationManagement;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import it.lvsemergency.areaInformationManagement.alarm.Alarm;
import it.lvsemergency.areaInformationManagement.data.AprsData;

@RestController
public class AreaController {

	private AreaInformationManagementIF areaService;

	@Autowired
	public AreaController(AreaService userService) {
		this.areaService = userService;
	}

	@GetMapping(path = "/areas")
	public List<Area> getAreas() {
		return areaService.getAreas();
	}

	@GetMapping(path = "/aprsdata")
	public List<AprsData> getAprsData() {
		return areaService.getAprsDatas();
	}

	/**
	 * get last aprs data of a particular area
	 * 
	 * @param idArea area of interest
	 * @return aprs station data
	 */

	@GetMapping(path = "/areas/{idArea}/aprsdata")
	public AprsData getAprsDataByIdArea(@PathVariable Integer idArea) {
		return areaService.getAprsDataByIdArea(idArea);
	}

	/**
	 * get last fog or frost alarm of a area
	 * 
	 * @param idArea area of interest
	 * @return last fog or frost alarm if present in a particular area
	 */
	@GetMapping(path = "/areas/{idArea}/alarms/fogorfrost")
	public Alarm getFogOrFrostAlarmByIdArea(@PathVariable Integer idArea) {
		return areaService.getFogOrFrostAlarmByIdArea(idArea);
	}

	/**
	 * get last bad weather alarm of a area
	 * 
	 * @param idArea area of interest
	 * @return last bad weather alarm if present in a particular area
	 */
	@GetMapping(path = "/areas/{idArea}/alarms/badweather")
	public Alarm getBadWeatherByIdArea(@PathVariable Integer idArea) {
		return areaService.getBadWeatherByIdArea(idArea);
	}

}
