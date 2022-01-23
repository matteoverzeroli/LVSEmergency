#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QJsonObject>

#include "./helpers/entityif.h"

namespace areaInformationManagementIF {
class Area : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY(QString areaName READ getAreaName CONSTANT)
public:
    explicit Area(QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonObject(QJsonObject jsonObject);


    int getIdArea();
    void setIdArea(int newIdArea);

    QString getAreaName();
    void setAreaName(const QString &newAreaName);

    double getLat();
    void setLat(double newLat);

    double getLng();
    void setLng(double newLng);

    QString getIstatCode();
    void setIstatCode(const QString &newIstatCode);

signals:

private:
    int idArea;
    QString areaName;
    double lat;
    double lng;
    QString istatCode;

};
}

#endif // AREA_H
