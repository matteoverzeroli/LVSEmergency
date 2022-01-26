#ifndef AREACONTROLLER_H
#define AREACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "area.h"
#include "aprsdata.h"

namespace areaInformationManagementIF {

class AreaController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList areasAvailableList READ getAreasAvailableList NOTIFY areasAvailableListChanged)
    Q_PROPERTY(areaInformationManagementIF::AprsData *aprsData READ getAprsData NOTIFY aprsDataChanged)
public:
    explicit AreaController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);

    Q_INVOKABLE void getAreas();
    Q_INVOKABLE int getIdAreaByName(QString areaName);
    Q_INVOKABLE void getAprsData(int idArea);
    QStringList getAreasAvailableList();
    AprsData *getAprsData();

signals:
    void areasAvailableListChanged();
    void aprsDataChanged();

private slots:
    void allAreasReceived();
    void aprsdataReceived();

private:
    QNetworkAccessManager *networkManager {nullptr};
    QList<Area *> availableAreas;

    AprsData *aprsData {nullptr};

};

}

#endif // AREACONTROLLER_H
