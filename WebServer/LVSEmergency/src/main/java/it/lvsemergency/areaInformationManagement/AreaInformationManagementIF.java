package it.lvsemergency.areaInformationManagement;

import java.util.List;

import it.lvsemergency.areaInformationManagement.alarm.Alarm;
import it.lvsemergency.areaInformationManagement.data.AprsData;

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
	
	/**
	 * Restituisce tutti i dati APRS presenti nel sistema.
	 * 
	 * @return List<AprsData> lista di dati presenti nel sistema.
	 */
	public List<AprsData> getAprsDatas();
	
	/**
	 * Restituisce l'ultimo dato APRS di una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere il dato APRS.
	 * @return AprsData Dati APRS dell'area.
	 */
	public AprsData getAprsDataByIdArea(Integer idArea);

	/**
	 * Restistuisce l'ultimo allarme presente relativo al maltempo per una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere l'allarme.
	 * @return Alarm Ultimo allarme disponibile.
	 */
	public Alarm getBadWeatherByIdArea(Integer idArea);

	/**
	 * Restistuisce l'ultimo allarme presente relativo a nebbia o brina per una specifica area.
	 * 
	 * @param idArea id dell'area di cui si vuole ricevere l'allarme.
	 * @return Alarm Ultimo allarme disponibile.
	 */
	public Alarm getFogOrFrostAlarmByIdArea(Integer idArea);
}
