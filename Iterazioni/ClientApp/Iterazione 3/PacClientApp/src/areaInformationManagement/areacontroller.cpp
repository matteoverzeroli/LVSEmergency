#include "areacontroller.h"

#include <QJsonArray>

#include "./helpers/utils.h"

namespace areaInformationManagement {
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
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/areas"));
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
/*!
 * \brief Funzione per invocare l'API che richiede i dati aprs dell'area idArea.
 */
void AreaController::getAprsData(int idArea)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/areas/" + QString::number(idArea) + "/aprsdata"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &AreaController::aprsdataReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che richiede i dati aprs.
 */
void AreaController::aprsdataReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        if (aprsData != nullptr)
            delete aprsData;

        aprsData = new AprsData(this);
        aprsData->fromJsonObject(QJsonDocument::fromJson(response).object());

        emit aprsDataChanged();
    } else {
        qDebug() << "Error:" << reply->error();
        emit aprsDataError();
    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che richiede gli allarmi di nebbia.
 */
void AreaController::getAlarmsFogOrFrost(int idArea)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/areas/" + QString::number(idArea) + "/alarms/fogorfrost"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &AreaController::alarmReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che richiede gli allarmi.
 */
void AreaController::alarmReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        if (frogorfrostAlarm != nullptr)
            delete frogorfrostAlarm;

        frogorfrostAlarm = new Alarm(this);
        frogorfrostAlarm->fromJsonObject(QJsonDocument::fromJson(response).object());

        emit frogorfrostAlarmChanged();
    } else {
        qDebug() << "Error:" << reply->error();
        emit frogorfrostAlarmError();
    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che richiede gli allarmi di mal tempo.
 */
void AreaController::getAlarmsBadWheather(int idArea)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/areas/" + QString::number(idArea) + "/alarms/badweather"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &AreaController::alarmsBadWheatherReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che richiede gli allarmi.
 */
void AreaController::alarmsBadWheatherReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        if (badwheatherAlarm != nullptr)
            delete badwheatherAlarm;

        badwheatherAlarm = new Alarm(this);
        badwheatherAlarm->fromJsonObject(QJsonDocument::fromJson(response).object());

        emit badWheatherAlarmChanged();
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

AprsData *AreaController::getAprsData()
{
    return aprsData;
}

Alarm *AreaController::getFrogOrFrostAlarm()
{
    return frogorfrostAlarm;
}

Alarm *AreaController::getBadWheatherAlarm()
{
    return badwheatherAlarm;
}

}
