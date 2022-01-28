#include "aprsdata.h"

namespace areaInformationManagementIF {
AprsData::AprsData(QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
}

QJsonDocument AprsData::toJsonDocument()
{
    return QJsonDocument::fromJson("");
}

void AprsData::fromJsonObject(QJsonObject jsonObject)
{
    name = jsonObject.value("name").toString();
    date = QDateTime::fromString(jsonObject.value("time").toString(), "dd-MM-yyyy HH:mm:ss");
    temperature = jsonObject.value("temperature").toDouble();
    pressure = jsonObject.value("pressure").toDouble();
    humidity = jsonObject.value("humidity").toDouble();
    windDirection = jsonObject.value("windDirection").toDouble();
    windSpeed = jsonObject.value("windSpeed").toDouble();
    windGust = jsonObject.value("windGust").toDouble();
    rainOneHour = jsonObject.value("rainOneHour").toDouble();
    rainDay = jsonObject.value("rainDay").toDouble();
    rainMidNight = jsonObject.value("rainMidNight").toDouble();
    luminosity = jsonObject.value("luminosity").toDouble();
}

QString AprsData::getName()
{
    return name;
}

void AprsData::setName(QString newName)
{
    name = newName;
}

QString AprsData::getDate()
{
    return date.toString("dd-MM-yyyy HH:mm:ss");
}

void AprsData::setDate(QDateTime newDate)
{
    date = newDate;
}

float AprsData::getTemperature() const
{
    return temperature;
}

void AprsData::setTemperature(float newTemperature)
{
    temperature = newTemperature;
}

float AprsData::getPressure() const
{
    return pressure;
}

void AprsData::setPressure(float newPressure)
{
    pressure = newPressure;
}

int AprsData::getHumidity() const
{
    return humidity;
}

void AprsData::setHumidity(int newHumidity)
{
    humidity = newHumidity;
}

float AprsData::getWindDirection() const
{
    return windDirection;
}

void AprsData::setWindDirection(float newWindDirection)
{
    windDirection = newWindDirection;
}

float AprsData::getWindSpeed() const
{
    return windSpeed;
}

void AprsData::setWindSpeed(float newWindSpeed)
{
    windSpeed = newWindSpeed;
}

float AprsData::getWindGust() const
{
    return windGust;
}

void AprsData::setWindGust(float newWindGust)
{
    windGust = newWindGust;
}

float AprsData::getRainOneHour() const
{
    return rainOneHour;
}

void AprsData::setRainOneHour(float newRainOneHour)
{
    rainOneHour = newRainOneHour;
}

float AprsData::getRainDay() const
{
    return rainDay;
}

void AprsData::setRainDay(float newRainDay)
{
    rainDay = newRainDay;
}

float AprsData::getRainMidNight() const
{
    return rainMidNight;
}

void AprsData::setRainMidNight(float newRainMidNight)
{
    rainMidNight = newRainMidNight;
}

float AprsData::getLuminosity() const
{
    return luminosity;
}

void AprsData::setLuminosity(float newLuminosity)
{
    luminosity = newLuminosity;
}
}
