#include "userController.h"

#include <QDebug>
#include <QSettings>
#include <QTimer>

#include "./helpers/utils.h"


namespace accountmanagementIF {
UserController::UserController(QNetworkAccessManager *networkManager,
                               NavigationController *navigationController, QObject *parent)
    : QObject{parent},
      networkManager(networkManager),
      navigationController(navigationController)
{

}

/*!
 * \brief Funzione per invocare l'API che esegue il login.
 */
void UserController::login(QString username, QString password)
{
    QSettings settings;
    settings.beginGroup("Credentials");
    settings.setValue("username", username);
    settings.setValue("password", password);
    settings.endGroup();

    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/login"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::responseReceived);
    connect(reply, &QNetworkReply::errorOccurred, this, &UserController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &UserController::sslErrors);
}

void UserController::responseReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        if (currentUser != nullptr)
            delete currentUser;

        currentUser = new User(QString(response), this);

        emit currentUserChanged(currentUser);

        navigationController->needDashboardView();
    } else {

        authenticationError = true;
        QTimer::singleShot(3000, this, [=](){
            authenticationError = false;
            emit authErrorChanged(authenticationError);
        });

        emit authErrorChanged(authenticationError);
    }

    reply->deleteLater();
}

void UserController::modifyUser()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/users"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->put(request, currentUser->toJsonDocument().toJson());
    connect(reply, &QNetworkReply::finished, this, &UserController::userModified);
    connect(reply, &QNetworkReply::errorOccurred, this, &UserController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &UserController::sslErrors);
}

void UserController::userModified()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        if (currentUser != nullptr)
            delete currentUser;

        currentUser = new User(QString(response), this);

        emit currentUserChanged(currentUser);

    } else {
        qDebug() << "Error!";
    }

    reply->deleteLater();
}

void UserController::errorReceived(QNetworkReply::NetworkError code)
{
    qDebug() << "Some error occoured:" << code;
}

void UserController::sslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors)
    qDebug() << "Some sslErrors occoured!";
}

bool UserController::getAuthError()
{
    return authenticationError;
}

User *UserController::getCurrentUser()
{
    return currentUser;
}

}
