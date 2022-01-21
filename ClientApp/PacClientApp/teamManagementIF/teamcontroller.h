#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "team.h"

namespace teamManagementIF {
class TeamController : public QObject
{
    Q_OBJECT
public:
    explicit TeamController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);

    Q_INVOKABLE void getTeams();

signals:

private slots:
    void allTeamsReceived();


private:
    QNetworkAccessManager *networkManager {nullptr};

    QList<Team *> extractTeamListFromJsonDoc(QJsonDocument jsonDocument);
};
}
#endif // TEAMCONTROLLER_H
