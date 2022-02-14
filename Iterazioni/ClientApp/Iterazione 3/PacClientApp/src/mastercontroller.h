#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>

#include "navigationcontroller.h"
#include "./accountManagement/userController.h"
#include "./teamManagement/teamcontroller.h"
#include "./areaInformationManagement/areacontroller.h"

/*!
 * \brief The MasterController class
 * \details Classe principale dell'applicazione.
 * Espone altre classi al QmlEngine.
 */

class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NavigationController *ui_navigationController READ getNavigationController CONSTANT)
    Q_PROPERTY(accountManagement::UserController *ui_userController READ getUserController CONSTANT)
    Q_PROPERTY(teamManagement::TeamController *ui_teamController READ getTeamController CONSTANT)
    Q_PROPERTY(areaInformationManagement::AreaController *ui_areaController READ getAreaController CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);

    NavigationController *getNavigationController();
    accountManagement::UserController *getUserController();
    teamManagement::TeamController *getTeamController();
    areaInformationManagement::AreaController *getAreaController();

signals:

private:
    NavigationController *navigationController {nullptr};
    accountManagement::UserController *userController {nullptr};
    teamManagement::TeamController *teamController {nullptr};
    areaInformationManagement::AreaController *areaController {nullptr};

    QNetworkAccessManager newtworkManager;

};

#endif // MASTERCONTROLLER_H
