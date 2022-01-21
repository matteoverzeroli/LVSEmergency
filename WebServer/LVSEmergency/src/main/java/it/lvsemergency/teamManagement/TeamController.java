package it.lvsemergency.teamManagement;

import java.util.List;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.http.HttpStatus;

@RestController
public class TeamController {

	private TeamService teamService;

	@Autowired
	public TeamController(TeamService userService) {
		this.teamService = userService;
	}

	@GetMapping(path = "/teams")
	public List<Team> getTeams() {
		return teamService.getTeams();
	}

	@GetMapping(path = "/teams/{idTeam}")
	public Team getTeam(@PathVariable Integer idTeam) {
		return teamService.getTeam(idTeam);
	}

	@PostMapping(path = "/teams")
	@ResponseStatus(HttpStatus.CREATED)
	public String addTeam(@Valid @RequestBody TeamDTO teamDto) {
		teamService.addTeam(teamDto);
		return "Team created successfully!";
	}

	@DeleteMapping(path = "/teams/{idTeam}")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public void deleteTeam(@PathVariable Integer idTeam) {
		teamService.deleteTeam(idTeam);
	}
	
	/**
	 * Set foreman of a team.
	 * 
	 * @param idTeam id of the team to be modified
	 * @param idForeman id of the user 
	 * 
	 * @return confirmation message
	 */
	
	@GetMapping(path = "/teams/foreman/{idTeam}/{idForeman}")
	@ResponseStatus(HttpStatus.ACCEPTED)
	public String setForemanTeam(@PathVariable Integer idTeam, @PathVariable Integer idForeman) {
		teamService.setForemanTeam(idTeam, idForeman);
		return "Foreman " + idForeman + " assigned to " + idTeam + " correctly !";
	}

}
