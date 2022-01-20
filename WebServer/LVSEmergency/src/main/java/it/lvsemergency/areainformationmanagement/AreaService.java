package it.lvsemergency.areainformationmanagement;

import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;


@Service
public class AreaService {
	
	@Autowired
	private AreaRepository areaRepository;
	
	public List<Area> getAreas() {
		return areaRepository.findAll();
	}
	
	public Area getArea(Integer idArea) {
		Optional<Area> area = areaRepository.findById(idArea);
		
		if (!area.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team found!");
		
		return area.get();
	}
}
