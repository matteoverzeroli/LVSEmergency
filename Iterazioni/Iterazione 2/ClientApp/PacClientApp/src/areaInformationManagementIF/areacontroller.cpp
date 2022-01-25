#include "areacontroller.h"

#include <QJsonArray>

#include "./helpers/utils.h"

namespace areaInformationManagementIF {
AreaController::AreaController(QNetworkAccessManager *networkManager, QObject *parent)
    : QObject{parent},
      networkManager(networkManager)
{

}

/*!
 * \brief Funzione per invocare l'API che richiede tutte le aree.
 */
void AreaController::getAreas()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/areas"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &AreaController::allAreasReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che richiede tutte le aree.
 */
void AreaController::allAreasReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        availableAreas.clear();

        QJsonArray areaArray = QJsonDocument::fromJson(response).array();
        foreach (const QJsonValue &areaValue, areaArray) {
            Area *newArea = new Area(this);
            newArea->fromJsonObject(areaValue.toObject());
            availableAreas.append(newArea);
        }

        emit areasAvailableListChanged();
    } else {
        qDebug() << "Error:" << reply->error();
    }

    reply->deleteLater();
}

int AreaController::getIdAreaByName(QString areaName)
{
    foreach (Area *area, availableAreas) {
        if (area->getAreaName() == areaName)
            return area->getIdArea();
    }

    return 0;
}

QStringList AreaController::getAreasAvailableList()
{
    QStringList areasNameList;
    foreach (Area *area, availableAreas) {
        areasNameList << area->getAreaName();
    }

    return areasNameList;
}

}
