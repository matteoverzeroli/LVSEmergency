package it.lvsemergency.areaInformationManagement;

import java.util.List;

public interface AreaInformationManagementIF {
	
	/**
	 * Restistuisce le aree presenti nel sistema.
	 * 
	 * @return List<Area> lista delle aree presenti.
	 */
	public List<Area> getAreas();

	/**
	 * Restistuisce una specifica area presente nel sistema.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere informazioni.
	 * @return Area richiesta.
	 */
	public Area getArea(Integer idArea);
}
