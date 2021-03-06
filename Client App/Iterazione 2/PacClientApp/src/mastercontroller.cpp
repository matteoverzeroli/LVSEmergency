#include "mastercontroller.h"

MasterController::MasterController(QObject *parent)
    : QObject{parent}
{
    navigationController = new NavigationController(this);
    userController = new accountmanagementIF::UserController(&newtworkManager,
                                                                navigationController,
                                                                this);
    teamController = new teamManagementIF::TeamController(&newtworkManager, this);
    areaController = new areaInformationManagementIF::AreaController(&newtworkManager, this);
}

NavigationController *MasterController::getNavigationController()
{
    return navigationController;
}

accountmanagementIF::UserController *MasterController::getUserController()
{
    return userController;
}

teamManagementIF::TeamController *MasterController::getTeamController()
{
    return teamController;
}

areaInformationManagementIF::AreaController *MasterController::getAreaController()
{
    return areaController;
}
