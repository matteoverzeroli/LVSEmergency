package it.lvsemergency.accountManagement.position;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import com.fasterxml.jackson.annotation.JsonFormat;

@Table(name = "position")
@Entity
public class Position {
	
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) int idPosition;
	
	private double lat;
	private double lng;
	
	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	
	private int idUser;
	
	public Position() {
		
	}
	
	public Position(int idPosition, double lat, double lng,
			Date time, int idUser) {
		this.idPosition = idPosition;
		this.lat = lat;
		this.lng = lng;
		this.time = time;
		this.idUser = idUser;
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
}
