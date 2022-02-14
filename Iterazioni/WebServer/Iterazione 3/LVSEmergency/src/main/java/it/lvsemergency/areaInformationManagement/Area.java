package it.lvsemergency.areaInformationManagement;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Table(name = "area")
@Entity
public class Area {
	private @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Integer idArea;

	private String areaName;
	private Double lat;
	private Double lng;
	private String nameAprsStation;
	private String istatCode;

	public Area() {

	}

	public Area(Integer idArea, Double lat, Double lng, String nameAprsStation, String istatCode) {
		super();
		this.idArea = idArea;
		this.lat = lat;
		this.lng = lng;
		this.nameAprsStation = nameAprsStation;
		this.istatCode = istatCode;
	}

	public Integer getIdArea() {
		return idArea;
	}

	public void setIdArea(Integer idArea) {
		this.idArea = idArea;
	}

	public String getAreaName() {
		return areaName;
	}

	public void setAreaName(String areaName) {
		this.areaName = areaName;
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
	
	public String getNameAprsStation() {
		return nameAprsStation;
	}
	
	public void setNameAprsStation(String nameAprsStation) {
		this.nameAprsStation = nameAprsStation;
	}

	public String getIstatCode() {
		return istatCode;
	}

	public void setIstatCode(String istatCode) {
		this.istatCode = istatCode;
	}
}
