#include "mastercontroller.h"

MasterController::MasterController(QObject *parent)
    : QObject{parent}
{
    navigationController = new NavigationController(this);
    authenticationController = new accountmanagementIF::AuthenticationController(&newtworkManager, this);
}

NavigationController *MasterController::getNavigationController()
{
    return navigationController;
}

accountmanagementIF::AuthenticationController *MasterController::getAuthenticationController()
{
    return authenticationController;
}
