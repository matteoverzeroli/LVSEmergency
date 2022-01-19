#include "mastercontroller.h"

MasterController::MasterController(QObject *parent)
    : QObject{parent}
{
    navigationController = new NavigationController(this);
    authenticationController = new accountmanagementIF::UserController(&newtworkManager,
                                                                       navigationController,
                                                                       this);
}

NavigationController *MasterController::getNavigationController()
{
    return navigationController;
}

accountmanagementIF::UserController *MasterController::getAuthenticationController()
{
    return authenticationController;
}
