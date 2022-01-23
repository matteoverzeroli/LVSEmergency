#include "area.h"

namespace areaInformationManagementIF {
Area::Area(QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
}

QJsonDocument Area::toJsonDocument()
{
    QJsonObject areaObject;
    areaObject.insert("idArea", idArea);
    areaObject.insert("areaName", areaName);
    areaObject.insert("lat", lat);
    areaObject.insert("lng", lng);
    areaObject.insert("istatCode", istatCode);

    return QJsonDocument(areaObject);
}

void Area::fromJsonObject(QJsonObject jsonObject)
{
    idArea = jsonObject.value("idArea").toInt();
    areaName = jsonObject.value("areaName").toString();
    lat = jsonObject.value("lat").toDouble();
    lng = jsonObject.value("lng").toDouble();
    istatCode = jsonObject.value("istatCode").toString();
}

int Area::getIdArea()
{
    return idArea;
}

void Area::setIdArea(int newIdArea)
{
    idArea = newIdArea;
}

QString Area::getAreaName()
{
    return areaName;
}

void Area::setAreaName(const QString &newAreaName)
{
    areaName = newAreaName;
}

double Area::getLat()
{
    return lat;
}

void Area::setLat(double newLat)
{
    lat = newLat;
}

double Area::getLng()
{
    return lng;
}

void Area::setLng(double newLng)
{
    lng = newLng;
}

QString Area::getIstatCode()
{
    return istatCode;
}

void Area::setIstatCode(const QString &newIstatCode)
{
    istatCode = newIstatCode;
}

}
