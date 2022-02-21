package it.lvsemergency.accountManagement.position;

import java.util.Optional;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;


public interface PositionRepository extends JpaRepository<Position, Integer>{

	@Query("select a from Position a where a.idUser = ?1")
	Optional<Position> findPositionByIdUser(Integer idUser, Sort sort, PageRequest limit);
	
}
