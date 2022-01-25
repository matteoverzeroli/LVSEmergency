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
        availableTeams.clear();

        QJsonArray teamArray = QJsonDocument::fromJson(response).array();
        foreach (const QJsonValue &teamObject, teamArray) {
            Team *newTeam = new Team(teamObject, this);
            availableTeams.append(newTeam);
        }

        emit teamsAvailableListChanged();
        emit teamsWithoutForemanChanged();
    } else {

    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che richiede il team dell'utente corrente.
 */
void TeamController::getTeam(int idTeam)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/teams/" + QString::number(idTeam)));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &TeamController::teamReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API che riceve un team specifico.
 */
void TeamController::teamReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {

        if (currentTeam != nullptr)
            delete currentTeam;

        currentTeam = new Team(this);
        currentTeam->fromJsonObject(QJsonDocument::fromJson(response).object());

        emit currentTeamChanged();
    } else {

    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che crea un nuovo team.
 */
void TeamController::addTeam(QString teamName, int idArea)
{
    QScopedPointer<Team> newTeam(new Team());
    newTeam->setTeamName(teamName);
    newTeam->setIdArea(idArea);

    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/teams"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkReply *reply = networkManager->post(request, newTeam->toJsonDocument().toJson());
    connect(reply, &QNetworkReply::finished, this, &TeamController::teamAdded);
}

/*!
 * \brief Slot che riceve la risposta dell'API che crea un nuovo team.
 */
void TeamController::teamAdded()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {

        qDebug() << "Aggiunto:" << reply->error();
        emit teamAddedWithSuccess();
    } else {

        qDebug() << "Error:" << reply->error();
        emit errorWhileAddingTeam();
    }

    reply->deleteLater();
}

int TeamController::getIdTeamByName(QString teamName)
{
    foreach (Team *team, availableTeams) {
        if (team->getTeamName() == teamName)
            return team->getIdTeam();
    }

    return 0;
}

QStringList TeamController::getTeamsAvailableList()
{
    QStringList teamsNameList;
    foreach (Team *team, availableTeams) {
        teamsNameList << team->getTeamName();
    }

    return teamsNameList;
}


QStringList TeamController::getTeamsAvailableWithoutForeman()
{
    QStringList teamsNameList;
    foreach (Team *team, availableTeams) {
        if (team->getIdForeman() == 0)
            teamsNameList << team->getTeamName();
    }

    return teamsNameList;
}

Team *TeamController::getCurrentTeam()
{
    return currentTeam;
}

}
