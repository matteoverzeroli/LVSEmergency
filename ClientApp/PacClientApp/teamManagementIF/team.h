#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QJsonArray>
#include "../accountManagementIF/user.h"

namespace teamManagementIF {
class Team : public QObject
{
    Q_OBJECT
public:
    explicit Team(QJsonValue teamObject, QObject *parent = nullptr);

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

signals:

private:
    int idTeam;
    QString teamName;
    int idForeman;
    QList<accountmanagementIF::User *> users;

};

}

#endif // TEAM_H
