package it.lvsemergency.areaInformationManagement.alarm;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import com.fasterxml.jackson.annotation.JsonFormat;

@Table(name = "alarm")
@Entity
public class Alarm {
	private @Id Integer idAlarm;
	
	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	
	@Enumerated(EnumType.STRING)
	private AlarmType type;
	
	@Enumerated(EnumType.STRING)
	private AlarmColor color;
	
	private Integer idArea;
	private String description;
	
	public Alarm() {
		
	}
	
	public Alarm(Integer idAlarm, Date time, AlarmType type, AlarmColor color, Integer idArea, String description) {
		super();
		this.idAlarm = idAlarm;
		this.time = time;
		this.type = type;
		this.color = color;
		this.idArea = idArea;
		this.description = description;
	}

	public Integer getIdAlarm() {
		return idAlarm;
	}
	public void setIdAlarm(Integer idAlarm) {
		this.idAlarm = idAlarm;
	}
	public Date getTime() {
		return time;
	}
	public void setTime(Date time) {
		this.time = time;
	}
	public AlarmType getType() {
		return type;
	}
	public void setType(AlarmType type) {
		this.type = type;
	}
	public AlarmColor getColor() {
		return color;
	}
	public void setColor(AlarmColor color) {
		this.color = color;
	}
	public Integer getIdArea() {
		return idArea;
	}
	public void setIdArea(Integer idArea) {
		this.idArea = idArea;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
}
