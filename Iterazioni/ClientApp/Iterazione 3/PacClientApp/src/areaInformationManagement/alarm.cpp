#include "alarm.h"

namespace areaInformationManagement {
Alarm::Alarm(QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
}

QJsonDocument Alarm::toJsonDocument()
{
    return QJsonDocument::fromJson("");
}

void Alarm::fromJsonObject(QJsonObject alarmObject)
{
    idArea = alarmObject.value("idArea").toInt();
    date = QDateTime::fromString(alarmObject.value("time").toString(), "dd-MM-yyyy HH:mm:ss");
    type = alarmObject.value("type").toString();
    color = alarmObject.value("color").toString();
    description = alarmObject.value("description").toString();
}

QString Alarm::getDate()
{
    return date.toString("dd-MM-yyyy HH:mm:ss");
}

void Alarm::setDate(const QDateTime &newDate)
{
    date = newDate;
}

QString Alarm::getType()
{
    return type;
}

void Alarm::setType(const QString &newType)
{
    type = newType;
}

QString Alarm::getColor()
{
    return color;
}

void Alarm::setColor(const QString &newColor)
{
    color = newColor;
}

int Alarm::getIdArea() const
{
    return idArea;
}

void Alarm::setIdArea(int newIdArea)
{
    idArea = newIdArea;
}

QString Alarm::getDescription()
{
    return description;
}

void Alarm::setDescription(const QString &newDescription)
{
    description = newDescription;
}
}
