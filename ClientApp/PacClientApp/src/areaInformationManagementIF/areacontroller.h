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
public:
    explicit AreaController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);

    Q_INVOKABLE void getAreas();
    Q_INVOKABLE int getIdAreaByName(QString areaName);
    Q_INVOKABLE void getAprsData(int idArea);
    Q_INVOKABLE void getAlarms(int idArea);
    QStringList getAreasAvailableList();
    AprsData *getAprsData();
    Alarm *getFrogOrFrostAlarm();

signals:
    void areasAvailableListChanged();
    void aprsDataChanged();
    void frogorfrostAlarmChanged();

private slots:
    void allAreasReceived();
    void aprsdataReceived();
    void alarmReceived();
private:
    QNetworkAccessManager *networkManager {nullptr};
    QList<Area *> availableAreas;

    AprsData *aprsData {nullptr};

    Alarm * frogorfrostAlarm {nullptr};

};

}

#endif // AREACONTROLLER_H
