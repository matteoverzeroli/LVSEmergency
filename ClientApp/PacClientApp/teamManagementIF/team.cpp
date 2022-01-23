#include "team.h"

namespace teamManagementIF {

Team::Team(QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
}

Team::Team(QJsonValue teamObject, QObject *parent)
    : helpers::EntityIF{}
{
    setParent(parent);
    fromJsonObject(teamObject.toObject());
}

QJsonDocument Team::toJsonDocument()
{
    QJsonObject teamObject;
    teamObject.insert("teamName", teamName);
    teamObject.insert("idArea", idArea);

    return QJsonDocument(teamObject);
}

void Team::fromJsonObject(QJsonObject jsonObject)
{
    idTeam = jsonObject.value("idTeam").toInt();
    teamName = jsonObject.value("teamName").toString();
    idForeman = jsonObject.value("idForeman").toInt();

    QJsonValue areaObject = jsonObject.value("area");
    area = new areaInformationManagementIF::Area(this);
    area->fromJsonObject(areaObject.toObject());

    QJsonValue usersObject = jsonObject.value("users");
    QJsonArray usersArray = usersObject.toArray();
    foreach (const QJsonValue & userValue, usersArray) {
        accountmanagementIF::User *user =
                new accountmanagementIF::User(userValue.toObject(), this);
        users.append(user);
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

areaInformationManagementIF::Area *Team::getArea() const
{
    return area;
}

void Team::setArea(areaInformationManagementIF::Area *newArea)
{
    area = newArea;
}

int Team::getIdArea()
{
    return idArea;
}

void Team::setIdArea(int newIdArea)
{
    idArea = newIdArea;
}

QQmlListProperty<accountmanagementIF::User> Team::getUsersQml()
{
    return QQmlListProperty<accountmanagementIF::User>(this, &users);
}


}
