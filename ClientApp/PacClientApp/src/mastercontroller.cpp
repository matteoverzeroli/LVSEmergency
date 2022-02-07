#include "mastercontroller.h"

MasterController::MasterController(QObject *parent)
    : QObject{parent}
{
    navigationController = new NavigationController(this);
    userController = new accountManagement::UserController(&newtworkManager,
                                                                navigationController,
                                                                this);
    teamController = new teamManagement::TeamController(&newtworkManager, this);
    areaController = new areaInformationManagement::AreaController(&newtworkManager, this);
}

NavigationController *MasterController::getNavigationController()
{
    return navigationController;
}

accountManagement::UserController *MasterController::getUserController()
{
    return userController;
}

teamManagement::TeamController *MasterController::getTeamController()
{
    return teamController;
}

areaInformationManagement::AreaController *MasterController::getAreaController()
{
    return areaController;
}
