package it.lvsemergency.teamManagement;

import java.util.List;
import java.util.Optional;

import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

@Service
public class TeamService implements TeamManagementIF{

	@Autowired
	private TeamRepository teamRepository;

	@Autowired
	private ModelMapper modelMapper;

	/**
	 * Restistuisce tutti i team presenti nel sistema.
	 * 
	 * @return List<Team> Team presenti nel sistema.
	 */
	@Override
	public List<Team> getTeams() {
		return teamRepository.findAll();
	}

	/**
	 * Inserisce un nuovo team nel sistema.
	 * 
	 * @param teamDto Informazioni sul nuovo team da inserire. 
	 */
	@Override
	public void addTeam(TeamDTO teamDto) {
		List<Team> teamInRepo = teamRepository.findByTeamName(teamDto.getTeamName());

		if (!teamInRepo.isEmpty())
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Team already exists!");

		Team newTeam = modelMapper.map(teamDto, Team.class);

		teamRepository.save(newTeam);
	}

	/**
	 * Restituisce un particolare Team.
	 * 
	 * @param idTeam id del Team di interesse.
	 * @return Team Informazioni riguardanti il team richiesto.
	 */
	@Override
	public Team getTeam(Integer idTeam) {
		Optional<Team> team = teamRepository.findById(idTeam);

		if (!team.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team found!");

		return team.get();
	}

	/**
	 * Cancella un team dal sistema.
	 * 
	 * @param idTeam id del team che si desidera cancellare. 
	 */
	@Override
	public void deleteTeam(Integer idTeam) {
		Optional<Team> teamToDelete = teamRepository.findById(idTeam);

		if (!teamToDelete.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team to delete!");

		teamRepository.delete(teamToDelete.get());
	}

	/**
	 * Imposta il caposquadra di un team.
	 * 
	 * @param idTeam id del team di cui deve essere importato il caposquadra.
	 * @param idForeman id del caposquadra da assegnare al team. 
	 */
	@Override
	public void setForemanTeam(Integer idTeam, Integer idForeman) {

		Optional<Team> team = teamRepository.findById(idTeam);
		
		if (!team.isPresent())
			throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No team found!");
		
		Team newTeam = team.get();
		newTeam.setIdForeman(idForeman);
		
		teamRepository.save(newTeam);
	}
}
