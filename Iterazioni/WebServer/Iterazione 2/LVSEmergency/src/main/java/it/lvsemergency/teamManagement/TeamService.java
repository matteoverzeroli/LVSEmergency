package it.lvsemergency.teamManagement;

import java.util.List;
import java.util.Optional;

import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

@Service
public class TeamService {

	@Autowired
	private TeamRepository teamRepository;

	@Autowired
	private ModelMapper modelMapper;

	public List<Team> getTeams() {
		return teamRepository.findAll();
	}

	public void addTeam(TeamDTO teamDto) {
		List<Team> teamInRepo = teamRepository.findByTeamName(teamDto.getTeamName());

		if (!teamInRepo.isEmpty())
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Team already exists!");

		Team newTeam = modelMapper.map(teamDto, Team.class);

		teamRepository.save(newTeam);
	}

	public Team getTeam(Integer idTeam) {
		Optional<Team> team = teamRepository.findById(idTeam);

		if (!team.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team found!");

		return team.get();
	}

	public void deleteTeam(Integer idTeam) {
		Optional<Team> teamToDelete = teamRepository.findById(idTeam);

		if (!teamToDelete.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team to delete!");

		teamRepository.delete(teamToDelete.get());
	}

	public void setForemanTeam(Integer idTeam, Integer idForeman) {

		Optional<Team> team = teamRepository.findById(idTeam);
		
		if (!team.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team found!");
		
		Team newTeam = team.get();
		newTeam.setIdForeman(idForeman);
		
		teamRepository.save(newTeam);
	}
}
