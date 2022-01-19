package it.lvsemergency.teamManagement;

import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;


@Service
public class TeamService {
	
	@Autowired
	private TeamRepository teamRepository;
	
	public List<Team> getTeams() {
		return teamRepository.findAll();
	}
	
	public Team addTeam(Team team) {
		List<Team> teamInRepo = teamRepository.findByTeamName(team.getTeamName());
		
		if (!teamInRepo.isEmpty())
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Team already exists");

		return teamRepository.save(team);
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
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team to delete");

		teamRepository.delete(teamToDelete.get());
	}
}
