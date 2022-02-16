#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QJsonObject>
#include <QDateTime>
#include "../helpers/entityif.h"

namespace accountManagement {

class Position : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY (QString date READ getDate CONSTANT)
    Q_PROPERTY (double latitude READ getLat CONSTANT)
    Q_PROPERTY (double longitude READ getLng CONSTANT)
    Q_PROPERTY (QString name READ getName CONSTANT)
    Q_PROPERTY (QString surname READ getSurname CONSTANT)
public:
    explicit Position(QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonObject(QJsonObject);

    int getIdPosition() const;
    void setIdPosition(int newIdPosition);

    int getIdUser() const;
    void setIdUser(int newIdUser);

    double getLat() const;
    void setLat(double newLat);

    double getLng() const;
    void setLng(double newLng);

    QString getDate();
    void setDate(QDateTime newDate);

    QString getName();
    QString getSurname();

signals:

private:
    int idPosition;
    int idUser;
    double lat;
    double lng;
    QDateTime date;
    QString name;
    QString surname;

};
}

#endif // POSITION_H
