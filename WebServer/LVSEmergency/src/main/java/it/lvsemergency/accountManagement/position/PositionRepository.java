package it.lvsemergency.accountManagement.position;

import java.util.List;
import java.util.Optional;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;


public interface PositionRepository extends JpaRepository<Position, Integer>{

	@Query("select a from Position a where a.idUser = ?1")
	Optional<Position> findPositionByIdUser(Integer idUser, Sort sort, PageRequest limit);
	
	@Query("select new it.lvsemergency.accountManagement.position.PositionDTO(p.idPosition,p.lat,p.lng,p.time,u.idUser,u.name,u.surname) "
			+ "from Position p join User u on p.idUser = u.idUser where u.state = 'ACTIVE' "
			+ "and u.idTeam = ?1 and "
			+ "p.time = (select max(time) from Position p1  where p1.idUser = u.idUser)")
	List<PositionDTO> test(Integer idTeam);
	
}
