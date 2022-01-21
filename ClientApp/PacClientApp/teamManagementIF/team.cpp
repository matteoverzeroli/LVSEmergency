#include "team.h"

namespace teamManagementIF {

Team::Team(QJsonValue teamObject, QObject *parent)
    : QObject{parent}
{
    fromJsonObject(teamObject.toObject());
}

QJsonDocument Team::toJsonDocument()
{

}

void Team::fromJsonObject(QJsonObject jsonObject)
{
    idTeam = jsonObject.value("idTeam").toInt();
    teamName = jsonObject.value("teamName").toString();
    idForeman = jsonObject.value("idForeman").toInt();

    QJsonValue usersObject = jsonObject.value("users");
    QJsonArray usersArray = usersObject.toArray();
    foreach (const QJsonValue & userObject, usersArray) {
        qDebug() << userObject;
//        accountmanagementIF::User *user =
//                new accountmanagementIF::User();
    }
}

int Team::getIdTeam()
{
    return idTeam;
}

void Team::setIdTeam(int newIdTeam)
{
    idTeam = newIdTeam;
}

QString Team::getTeamName()
{
    return teamName;
}

void Team::setTeamName(const QString &newTeamName)
{
    teamName = newTeamName;
}

int Team::getIdForeman()
{
    return idForeman;
}

void Team::setIdForeman(int newIdForeman)
{
    idForeman = newIdForeman;
}

QList<accountmanagementIF::User *> Team::getUsers()
{
    return users;
}

void Team::setUsers(const QList<accountmanagementIF::User *> &newUsers)
{
    users = newUsers;
}


}
