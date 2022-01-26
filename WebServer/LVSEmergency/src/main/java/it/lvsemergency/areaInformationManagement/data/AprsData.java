package it.lvsemergency.areaInformationManagement.data;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import com.fasterxml.jackson.annotation.JsonFormat;

@Table(name = "aprsdata")
@Entity
public class AprsData {
	private @Id String name;

	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	private Float temperature;
	private Float pressure;
	private Integer humidity;
	private Float windDirection;
	private Float windSpeed;
	private Float windGust;
	private Float rainOneHour;
	private Float rainDay;
	private Float rainMidNight;
	private Float luminosity;

	public AprsData() {

	}

	public AprsData(String name, Date time, Float temperature, Float pressure, Integer humidity, Float windDirection, Float windSpeed,
			Float windGust, Float rainOneHour, Float rainDay, Float rainMidNight, Float luminosity) {
		super();
		this.name = name;
		this.time = time;
		this.temperature = temperature;
		this.pressure = pressure;
		this.humidity = humidity;
		this.windDirection = windDirection;
		this.windSpeed = windSpeed;
		this.windGust = windGust;
		this.rainOneHour = rainOneHour;
		this.rainDay = rainDay;
		this.rainMidNight = rainMidNight;
		this.luminosity = luminosity;
	}

	public Float getTemperature() {
		return temperature;
	}

	public void setTemperature(Float temperature) {
		this.temperature = temperature;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Date getTime() {
		return time;
	}

	public void setTime(Date time) {
		this.time = time;
	}

	public Float getPressure() {
		return pressure;
	}

	public void setPressure(Float pressure) {
		this.pressure = pressure;
	}

	public Integer getHumidity() {
		return humidity;
	}

	public void setHumidity(Integer humidity) {
		this.humidity = humidity;
	}

	public Float getWindDirection() {
		return windDirection;
	}

	public void setWindDirection(Float windDirection) {
		this.windDirection = windDirection;
	}

	public Float getWindSpeed() {
		return windSpeed;
	}

	public void setWindSpeed(Float windSpeed) {
		this.windSpeed = windSpeed;
	}

	public Float getWindGust() {
		return windGust;
	}

	public void setWindGust(Float windGust) {
		this.windGust = windGust;
	}

	public Float getRainOneHour() {
		return rainOneHour;
	}

	public void setRainOneHour(Float rainOneHour) {
		this.rainOneHour = rainOneHour;
	}

	public Float getRainDay() {
		return rainDay;
	}

	public void setRainDay(Float rainDay) {
		this.rainDay = rainDay;
	}

	public Float getRainMidNight() {
		return rainMidNight;
	}

	public void setRainMidNight(Float rainMidNight) {
		this.rainMidNight = rainMidNight;
	}

	public Float getLuminosity() {
		return luminosity;
	}

	public void setLuminosity(Float luminosity) {
		this.luminosity = luminosity;
	}

}