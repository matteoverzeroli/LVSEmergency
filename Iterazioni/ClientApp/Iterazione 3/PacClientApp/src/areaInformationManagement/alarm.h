#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QJsonObject>
#include <QDateTime>
#include "../helpers/entityif.h"

namespace areaInformationManagement {
class Alarm : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY (QString date READ getDate CONSTANT)
    Q_PROPERTY (QString type READ getType CONSTANT)
    Q_PROPERTY (QString color READ getColor CONSTANT)
    Q_PROPERTY (QString description READ getDescription CONSTANT)
public:
    explicit Alarm(QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonObject(QJsonObject);

    QString getDate();
    void setDate(const QDateTime &newDate);

    QString getType();
    void setType(const QString &newType);

    QString getColor();
    void setColor(const QString &newColor);

    int getIdArea() const;
    void setIdArea(int newIdArea);

    QString getDescription();
    void setDescription(const QString &newDescription);

signals:

private:
    QDateTime date;
    QString type;
    QString color;
    int idArea;
    QString description;

};
}

#endif // ALARM_H
