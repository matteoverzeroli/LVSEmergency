#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include "../accountManagement/user.h"
#include "../areaInformationManagement/area.h"
#include "../helpers/entityif.h"

namespace teamManagement {
class Team : public helpers::EntityIF
{
    Q_OBJECT
    Q_PROPERTY(QString teamName READ getTeamName CONSTANT)
    Q_PROPERTY(QQmlListProperty<accountManagement::User> users READ getUsersQml CONSTANT)
    Q_PROPERTY(areaInformationManagement::Area *area READ getArea CONSTANT)
    Q_PROPERTY(QStringList usersId READ getUsersId CONSTANT)
    Q_PROPERTY(int idTeam READ getIdTeam CONSTANT)
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

    QList<accountManagement::User *> getUsers();
    void setUsers(const QList<accountManagement::User *> &newUsers);

    areaInformationManagement::Area *getArea() const;
    void setArea(areaInformationManagement::Area *newArea);

    int getIdArea();
    void setIdArea(int newIdArea);

    QStringList getUsersId();

    QQmlListProperty<accountManagement::User> getUsersQml();

signals:

private:
    int idTeam;
    QString teamName;
    int idForeman {0};
    int idArea;
    QList<accountManagement::User *> users;
    areaInformationManagement::Area *area {nullptr};
};

}

#endif // TEAM_H
