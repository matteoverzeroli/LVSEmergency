#ifndef AREACONTROLLER_H
#define AREACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "area.h"

namespace areaInformationManagementIF {

class AreaController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList areasAvailableList READ getAreasAvailableList NOTIFY areasAvailableListChanged)
public:
    explicit AreaController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);

    Q_INVOKABLE void getAreas();
    Q_INVOKABLE int getIdAreaByName(QString areaName);
    QStringList getAreasAvailableList();


signals:
    void areasAvailableListChanged();

private slots:
    void allAreasReceived();

private:
    QNetworkAccessManager *networkManager {nullptr};
    QList<Area *> availableAreas;

};

}

#endif // AREACONTROLLER_H
