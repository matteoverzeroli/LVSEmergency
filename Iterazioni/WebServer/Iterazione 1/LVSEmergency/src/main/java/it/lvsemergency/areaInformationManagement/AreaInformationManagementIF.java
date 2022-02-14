package it.lvsemergency.areaInformationManagement;

public interface AreaInformationManagementIF {
	
	/**
	 * Restistuisce le aree presenti nel sistema.
	 */
	public void getAreas();
	
	/**
	 * Inserisce le informazioni riguardanti la stazione APRS di un area.
	 * L'informazione principale è il codice univoco che identifica la stazione
	 * che serve per eseguire la chiamata REST.
	 */
	public void insertAPRSInformation();
	
	/**
	 * Inserisce le informazioni tramite cui effettuare una chiamata REST
	 * ad una stazione personalizzata installata sul territorio.
	 */
	public void insertCustomDeviceInformation();
	
	/**
	 * Restistuisce i dati meteo raccolti da una particolare stazione APRS.
	 */
	public void getAPRSInformation();
	
	/**
	 * Restistuisce i dati meteo ottenuti tramite openWheatherMap.
	 */
	public void getOpenWheatherMapInformation();
	
	/**
	 * Restistuice le informazioni su eventuali terremoti avvenuti in una certa area
	 * tramite l'API disponibile sui terremoti.
	 */
	public void getEarthquakeInformation();
	
	
	/**
	 * Restituisce le informazioni raccolte da un dispositivo custom.
	 */
	public void getCustomDeviceInformation();
	
	/**
	 * Restituisce i dati derivanti dai bollettini della protezione civile.
	 */
	public void getPCPOPInformation();
	
	/**
	 * Restituisce gli allarmi presenti in una determinata area.
	 */
	public void getAlarms();
}
