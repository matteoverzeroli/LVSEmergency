package it.lvsemergency.areaInformationManagement;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;


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

}
