package it.lvsemergency.areaInformationManagement;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import it.lvsemergency.areaInformationManagement.data.AprsData;


@RestController
public class AreaController {

	private AreaService areaService;

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

}
