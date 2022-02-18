package it.lvsemergency.accountManagement.position;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import org.hibernate.annotations.CreationTimestamp;
import org.springframework.lang.Nullable;

import com.fasterxml.jackson.annotation.JsonFormat;

@Table(name = "position")
@Entity
public class Position {
	
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idPosition;
	
	private Double lat;
	private Double lng;
	
	@CreationTimestamp
	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	
	private Integer idUser;
	
	public Position() {
		
	}
	
	public Position(Integer idPosition, Double lat, Double lng,
			Date time, Integer idUser) {
		this.idPosition = idPosition;
		this.lat = lat;
		this.lng = lng;
		this.time = time;
		this.idUser = idUser;
	}
	
	public Integer getIdPosition() {
		return idPosition;
	}

	public void setIdPosition(Integer idPosition) {
		this.idPosition = idPosition;
	}

	public Double getLat() {
		return lat;
	}

	public void setLat(Double lat) {
		this.lat = lat;
	}

	public Double getLng() {
		return lng;
	}

	public void setLng(Double lng) {
		this.lng = lng;
	}

	public Date getTime() {
		return time;
	}

	public void setTime(Date time) {
		this.time = time;
	}

	public Integer getIdUser() {
		return idUser;
	}

	public void setIdUser(Integer idUser) {
		this.idUser = idUser;
	}
}
