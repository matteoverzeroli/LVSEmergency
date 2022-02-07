#include "team.h"

namespace teamManagement {

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
    area = new areaInformationManagement::Area(this);
    area->fromJsonObject(areaObject.toObject());

    QJsonValue usersObject = jsonObject.value("users");
    QJsonArray usersArray = usersObject.toArray();
    foreach (const QJsonValue & userValue, usersArray) {
        accountManagement::User *user =
                new accountManagement::User(userValue.toObject(), this);
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

QList<accountManagement::User *> Team::getUsers()
{
    return users;
}

void Team::setUsers(const QList<accountManagement::User *> &newUsers)
{
    users = newUsers;
}

areaInformationManagement::Area *Team::getArea() const
{
    return area;
}

void Team::setArea(areaInformationManagement::Area *newArea)
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

QQmlListProperty<accountManagement::User> Team::getUsersQml()
{
    return QQmlListProperty<accountManagement::User>(this, &users);
}


}
