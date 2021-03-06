#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "team.h"

namespace teamManagement {
class TeamController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList teamsAvailableList READ getTeamsAvailableList NOTIFY teamsAvailableListChanged)
    Q_PROPERTY(QStringList teamsAvailableWithoutForeman READ getTeamsAvailableWithoutForeman NOTIFY teamsWithoutForemanChanged)
    Q_PROPERTY(Team *currentTeam READ getCurrentTeam  NOTIFY currentTeamChanged)
public:
    explicit TeamController(QNetworkAccessManager *networkManager,
                            QObject *parent = nullptr);
    ~TeamController() override;

    Q_INVOKABLE void getTeams();
    Q_INVOKABLE void getTeam(int idTeam);
    Q_INVOKABLE void addTeam(QString teamName, int idArea);
    Q_INVOKABLE int getIdTeamByName(QString teamName);
    Q_INVOKABLE void resetTeam();
    QStringList getTeamsAvailableList();
    QStringList getTeamsAvailableWithoutForeman();
    Team *getCurrentTeam();
signals:
    void teamsAvailableListChanged();
    void teamsWithoutForemanChanged();
    void teamAddedWithSuccess();
    void errorWhileAddingTeam();
    void currentTeamChanged();

private slots:
    void allTeamsReceived();    
    void teamAdded();
    void teamReceived();
private:
    QNetworkAccessManager *networkManager {nullptr};
    QList<Team *> availableTeams;
    Team *currentTeam {nullptr};

};
}
#endif // TEAMCONTROLLER_H
