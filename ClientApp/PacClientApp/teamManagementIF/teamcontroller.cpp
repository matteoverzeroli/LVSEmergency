#include "teamcontroller.h"

#include "./helpers/utils.h"

namespace teamManagementIF {

TeamController::TeamController(QNetworkAccessManager *networkManager, QObject *parent)
    : QObject{parent},
      networkManager(networkManager)
{

}

/*!
 * \brief Funzione per invocare l'API che richiede tutti i team.
 */
void TeamController::getTeams()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/teams"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &TeamController::allTeamsReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che richiede tutti i team.
 */
void TeamController::allTeamsReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        //extractTeamListFromJsonDoc(QJsonDocument::fromJson(response));
    } else {

    }

    reply->deleteLater();
}

QList<Team*> TeamController::extractTeamListFromJsonDoc(QJsonDocument jsonDocument)
{
    QJsonArray teamArray = jsonDocument.array();
    foreach (const QJsonValue &teamObject, teamArray) {
        Team *newTeam = new Team(teamObject);
    }
}



}
