#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include "../accountManagementIF/user.h"
#include "../areaInformationManagementIF/area.h"
#include "../helpers/entityif.h"

namespace teamManagementIF {
class Team : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY(QString teamName READ getTeamName CONSTANT)
    Q_PROPERTY(QQmlListProperty<accountmanagementIF::User> users READ getUsersQml CONSTANT)
    Q_PROPERTY(areaInformationManagementIF::Area *area READ getArea CONSTANT)
public:
    explicit Team(QJsonValue teamObject, QObject *parent = nullptr);
    explicit Team(QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonObject(QJsonObject jsonDocument);

    int getIdTeam();
    void setIdTeam(int newIdTeam);

    QString getTeamName();
    void setTeamName(const QString &newTeamName);

    int getIdForeman();
    void setIdForeman(int newIdForeman);

    QList<accountmanagementIF::User *> getUsers();
    void setUsers(const QList<accountmanagementIF::User *> &newUsers);

    areaInformationManagementIF::Area *getArea() const;
    void setArea(areaInformationManagementIF::Area *newArea);

    int getIdArea();
    void setIdArea(int newIdArea);

    QQmlListProperty<accountmanagementIF::User> getUsersQml();

signals:

private:
    int idTeam;
    QString teamName;
    int idForeman {0};
    int idArea;
    QList<accountmanagementIF::User *> users;
    areaInformationManagementIF::Area *area {nullptr};
};

}

#endif // TEAM_H
