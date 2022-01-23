#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>

#include "navigationcontroller.h"
#include "./accountManagementIF/userController.h"
#include "./teamManagementIF/teamcontroller.h"
#include "./areaInformationManagementIF/areacontroller.h"

/*!
 * \brief The MasterController class
 * \details Classe principale per l'applicazione.
 */

class MasterController : public QObject
{
    Q_OBJECT
    // rendo accessibili le classi al lato QML
    Q_PROPERTY(NavigationController *ui_navigationController READ getNavigationController CONSTANT)
    Q_PROPERTY(accountmanagementIF::UserController *ui_userController READ getUserController CONSTANT)
    Q_PROPERTY(teamManagementIF::TeamController *ui_teamController READ getTeamController CONSTANT)
    Q_PROPERTY(areaInformationManagementIF::AreaController *ui_areaController READ getAreaController CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);

    NavigationController *getNavigationController();
    accountmanagementIF::UserController *getUserController();
    teamManagementIF::TeamController *getTeamController();
    areaInformationManagementIF::AreaController *getAreaController();

signals:

private:
    NavigationController *navigationController {nullptr};
    accountmanagementIF::UserController *userController {nullptr};
    teamManagementIF::TeamController *teamController {nullptr};
    areaInformationManagementIF::AreaController *areaController {nullptr};

    QNetworkAccessManager newtworkManager;

};

#endif // MASTERCONTROLLER_H
