#include "userController.h"

#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QJsonArray>

#include "./helpers/utils.h"


namespace accountmanagementIF {
UserController::UserController(QNetworkAccessManager *networkManager,
                               NavigationController *navigationController, QObject *parent)
    : QObject{parent},
      networkManager(networkManager),
      navigationController(navigationController)
{

}

UserController::~UserController()
{
    qDebug() << "UserController destructor";
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
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/login"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::responseReceived);
    connect(reply, &QNetworkReply::errorOccurred, this, &UserController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &UserController::sslErrors);
}

/*!
 * \brief Slot che riceve la risposta dell'API per il login.
 */
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

/*!
 * \brief Funzione per invocare l'API di modifica dello User.
 */
void UserController::modifyUser()
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkReply *reply = networkManager->put(request, currentUser->toJsonDocument().toJson());
    connect(reply, &QNetworkReply::finished, this, &UserController::userModified);
    connect(reply, &QNetworkReply::errorOccurred, this, &UserController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &UserController::sslErrors);
}

/*!
 * \brief Slot che riceve la risposta dell'API per la modifica.
 */
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

/*!
 * \brief Funzione per invocare l'API di aggiunta User.
 */
void UserController::addUser(QString userName, QString name, QString surname,
                             QString password, QString cf, QString address,
                             QString cellNumber, QString email, int role, int idTeam, QString sex)
{
    QScopedPointer<User> newUser(new User());
    newUser->setUsername(userName);
    newUser->setName(name);
    newUser->setSurname(surname);
    newUser->setPassword(password);
    newUser->setCf(cf);
    newUser->setAddress(address);
    newUser->setCellnumber(cellNumber);
    newUser->setEmail(email);
    newUser->setRole(role == 2 ? "VOLUNTEER" : "FOREMAN");
    newUser->setTeam(idTeam);
    newUser->setSex(sex);
    newUser->setState("INACTIVE");

    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkReply *reply = networkManager->post(request, newUser->toJsonDocument().toJson());
    connect(reply, &QNetworkReply::finished, this, &UserController::userAdded);
}

/*!
 * \brief Slot che riceve la risposta dell'API per l'aggiunta.
 */
void UserController::userAdded()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        emit userAddedWithSuccess();
    } else {
        emit errorOnAddingNewUser();
    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che richiede tutti gli utenti inseriti.
 */
void UserController::getUsers()
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::allUsersReceived);
}

/*!
 * \brief Slot che riceve la risposta dell'API di ricezione utenti.
 */
void UserController::allUsersReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        allUsers.clear();

        QJsonArray usersArray = QJsonDocument::fromJson(response).array();
        foreach (const QJsonValue &userValue, usersArray) {
            User *newUser = new User(userValue.toObject(), this);
            allUsers.append(newUser);
        }

        emit usersChanged(getAllUsers());
    } else {

    }

    reply->deleteLater();
}

/*!
 * \brief Funzione per invocare l'API che cancella un utente.
 */
void UserController::deleteUser(int idUser)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getWebServerPrefix() + "/users/" + QString::number(idUser)));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

    QNetworkReply *reply = networkManager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::userDeleted);
}

/*!
 * \brief Slot che riceve la risposta dell'API di ricezione utenti.
 */
void UserController::userDeleted()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        emit userDeletedWithSuccess();
    } else {
        emit errorWhileDeletingUser();
    }

    this->getUsers();

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

QQmlListProperty<User> UserController::getAllUsers()
{
    return QQmlListProperty<accountmanagementIF::User>(this, &allUsers);
}

}
