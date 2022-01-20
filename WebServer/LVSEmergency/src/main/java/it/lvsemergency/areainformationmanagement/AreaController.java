package it.lvsemergency.areainformationmanagement;

import java.util.List;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class AreaController {

	private AreaService areaService;

	@Autowired
	public AreaController(AreaService userService) {
		this.areaService = userService;
	}

	@GetMapping(path = "/areas")
	public List<Area> getTeams() {
		return areaService.getAreas();
	}

}
