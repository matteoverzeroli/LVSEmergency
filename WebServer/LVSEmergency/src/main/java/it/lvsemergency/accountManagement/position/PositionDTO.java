package it.lvsemergency.accountManagement.position;

import java.util.Date;

import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import com.fasterxml.jackson.annotation.JsonFormat;

public class PositionDTO {

	private int idPosition;
	private double lat;
	private double lng;
	
	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	
	private int idUser;	

	private String name;
	private String surname;
	
	public PositionDTO(Position pos) {
		this.idPosition = pos.getIdPosition();
		this.idUser = pos.getIdUser();
		this.lat = pos.getLat();
		this.lng = pos.getLng();
		this.time = pos.getTime();
	}
	
	public PositionDTO(int idPosition, double lat, double lng,
			Date time, int idUser, String name, String surname) {
		this.idPosition = idPosition;
		this.lat = lat;
		this.lng = lng;
		this.time = time;
		this.idUser = idUser;
		this.name= name;
		this.surname = surname;
	}
	
	public int getIdPosition() {
		return idPosition;
	}

	public void setIdPosition(int idPosition) {
		this.idPosition = idPosition;
	}

	public double getLat() {
		return lat;
	}

	public void setLat(double lat) {
		this.lat = lat;
	}

	public double getLng() {
		return lng;
	}

	public void setLng(double lng) {
		this.lng = lng;
	}

	public Date getTime() {
		return time;
	}

	public void setTime(Date time) {
		this.time = time;
	}

	public int getIdUser() {
		return idUser;
	}

	public void setIdUser(int idUser) {
		this.idUser = idUser;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}
	
	
}
