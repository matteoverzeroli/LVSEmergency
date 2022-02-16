#include "position.h"


namespace accountManagement {

Position::Position(QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
}

QJsonDocument Position::toJsonDocument()
{
    return QJsonDocument::fromJson("");
}

void Position::fromJsonObject(QJsonObject positionObject)
{
    idPosition = positionObject.value("idPosition").toInt();
    date = QDateTime::fromString(positionObject.value("time").toString(), "dd-MM-yyyy HH:mm:ss");
    lat = positionObject.value("lat").toDouble();
    lng = positionObject.value("lng").toDouble();
    idUser = positionObject.value("idUser").toInt();
    name = positionObject.value("name").toString();
    surname = positionObject.value("surname").toString();
}

int Position::getIdPosition() const
{
    return idPosition;
}

void Position::setIdPosition(int newIdPosition)
{
    idPosition = newIdPosition;
}

int Position::getIdUser() const
{
    return idUser;
}

void Position::setIdUser(int newIdUser)
{
    idUser = newIdUser;
}

double Position::getLat() const
{
    return lat;
}

void Position::setLat(double newLat)
{
    lat = newLat;
}

double Position::getLng() const
{
    return lng;
}

void Position::setLng(double newLng)
{
    lng = newLng;
}

QString Position::getDate()
{
    return date.toString("dd-MM-yyyy HH:mm:ss");;
}

void Position::setDate(QDateTime newDate)
{
    date = newDate;
}

QString Position::getName()
{
    return name;
}

QString Position::getSurname()
{
    return surname;
}

}
