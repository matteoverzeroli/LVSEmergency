package it.lvsemergency.areaInformationManagement.data;

import java.io.Serializable;
import java.util.Date;
import java.util.Objects;

import javax.persistence.Embeddable;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import com.fasterxml.jackson.annotation.JsonFormat;

@SuppressWarnings("serial")
@Embeddable
public class AprsDataId implements Serializable{

	private String name;
	@Temporal(TemporalType.TIMESTAMP)
	@JsonFormat(pattern="dd-MM-yyyy HH:mm:ss")
	private Date time;
	
	public AprsDataId() {

	}
	
	public AprsDataId(String name, Date time) {
		super();
		this.name = name;
		this.time = time;
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
	
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AprsDataId aprsDataId = (AprsDataId) o;
        return name.equals(aprsDataId.name) &&
                time.equals(aprsDataId.time);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, time);
    }
	
}
