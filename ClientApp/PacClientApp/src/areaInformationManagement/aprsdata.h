#ifndef APRSDATA_H
#define APRSDATA_H

#include <QObject>
#include <QDate>

#include "../helpers/entityif.h"

namespace areaInformationManagementIF {
class AprsData : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString date READ getDate CONSTANT)
    Q_PROPERTY(float temperature READ getTemperature CONSTANT)
    Q_PROPERTY(float pressure READ getPressure CONSTANT)
    Q_PROPERTY(float humidity READ getHumidity CONSTANT)
    Q_PROPERTY(float windDirection READ getWindDirection CONSTANT)
    Q_PROPERTY(float windSpeed READ getWindSpeed CONSTANT)
    Q_PROPERTY(float windGust READ getWindGust CONSTANT)
    Q_PROPERTY(float rainOneHour READ getRainOneHour CONSTANT)
    Q_PROPERTY(float rainDay READ getRainDay CONSTANT)
    Q_PROPERTY(float rainMidNight READ getRainMidNight CONSTANT)
    Q_PROPERTY(float luminosity READ getLuminosity CONSTANT)
public:
    explicit AprsData(QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonObject(QJsonObject jsonDocument);

    QString getName();
    void setName(QString newName);

    QString getDate();
    void setDate(QDateTime newDate);

    float getTemperature() const;
    void setTemperature(float newTemperature);

    float getPressure() const;
    void setPressure(float newPressure);

    int getHumidity() const;
    void setHumidity(int newHumidity);

    float getWindDirection() const;
    void setWindDirection(float newWindDirection);

    float getWindSpeed() const;
    void setWindSpeed(float newWindSpeed);

    float getWindGust() const;
    void setWindGust(float newWindGust);

    float getRainOneHour() const;
    void setRainOneHour(float newRainOneHour);

    float getRainDay() const;
    void setRainDay(float newRainDay);

    float getRainMidNight() const;
    void setRainMidNight(float newRainMidNight);

    float getLuminosity() const;
    void setLuminosity(float newLuminosity);

signals:

private:
    QString name;
    QDateTime date;
    float temperature;
    float pressure;
    int humidity;
    float windDirection;
    float windSpeed;
    float windGust;
    float rainOneHour {0};
    float rainDay {0};
    float rainMidNight {0};
    float luminosity;
};
}

#endif // APRSDATA_H
