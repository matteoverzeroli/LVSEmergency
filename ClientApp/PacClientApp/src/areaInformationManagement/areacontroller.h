#ifndef AREACONTROLLER_H
#define AREACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "area.h"
#include "aprsdata.h"
#include "alarm.h"

namespace areaInformationManagementIF {

class AreaController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList areasAvailableList READ getAreasAvailableList NOTIFY areasAvailableListChanged)
    Q_PROPERTY(areaInformationManagementIF::AprsData *aprsData READ getAprsData NOTIFY aprsDataChanged)
    Q_PROPERTY(areaInformationManagementIF::Alarm *frogorfrostAlarm READ getFrogOrFrostAlarm NOTIFY frogorfrostAlarmChanged)
    Q_PROPERTY(areaInformationManagementIF::Alarm *badwheatherAlarm READ getBadWheatherAlarm NOTIFY badWheatherAlarmChanged)
public:
    explicit AreaController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);

    Q_INVOKABLE void getAreas();
    Q_INVOKABLE int getIdAreaByName(QString areaName);
    Q_INVOKABLE void getAprsData(int idArea);
    Q_INVOKABLE void getAlarmsFogOrFrost(int idArea);
    Q_INVOKABLE void getAlarmsBadWheather(int idArea);
    QStringList getAreasAvailableList();
    AprsData *getAprsData();
    Alarm *getFrogOrFrostAlarm();
    Alarm *getBadWheatherAlarm();

signals:
    void areasAvailableListChanged();
    void aprsDataChanged();
    void frogorfrostAlarmChanged();
    void badWheatherAlarmChanged();


private slots:
    void allAreasReceived();
    void aprsdataReceived();
    void alarmReceived();
    void alarmsBadWheatherReceived();
private:
    QNetworkAccessManager *networkManager {nullptr};
    QList<Area *> availableAreas;

    AprsData *aprsData {nullptr};

    Alarm * frogorfrostAlarm {nullptr};
    Alarm * badwheatherAlarm {nullptr};
};

}

#endif // AREACONTROLLER_H
