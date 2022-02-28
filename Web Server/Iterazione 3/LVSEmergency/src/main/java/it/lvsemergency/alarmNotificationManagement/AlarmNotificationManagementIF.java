package it.lvsemergency.alarmNotificationManagement;

public interface AlarmNotificationManagementIF {

	/**
	 * Imposta da quale tipo di allarme si vuole ricevere una notifica.
	 */
	public void chooseTypeAlarmToBeNotify();
	
	/**
	 * Modifica il tipo di allarme di cui si vuole ricevere notifica.
	 */
	public void modifyTypeAlarmToBeNotify();
	
	/**
	 * Elimina un tipo di allarme da quelli di cui si vuole ricevere notifica.
	 */
	public void deleteTypeAlarmToBeNotify();
}
