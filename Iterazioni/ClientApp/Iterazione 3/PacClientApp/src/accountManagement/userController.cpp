#include "userController.h"

#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QJsonArray>

#include "./helpers/utils.h"


namespace accountManagement {
UserController::UserController(QNetworkAccessManager *networkManager,
                               NavigationController *navigationController, QObject *parent)
    : QObject{parent},
      networkManager(networkManager),
      navigationController(navigationController)
{

    source = QGeoPositionInfoSource::createDefaultSource(0);
    if (source) {
        qDebug() << "We have a valid geoPosition source.";
        source->setUpdateInterval(10000);
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &UserController::positionReceived);
        connect(source, QOverload<QGeoPositionInfoSource::Error>::of(&QGeoPositionInfoSource::error),
                [=](QGeoPositionInfoSource::Error positioningError){
            qDebug() << "Positioning error: " << positioningError;
        });
    }
}

UserController::~UserController()
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
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/login"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());

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

        if (source) {
            source->startUpdates();
        }

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
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());
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
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());
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
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        QScopedPointer<User> newUser(new User());
        newUser->fromJsonDocument(QJsonDocument::fromJson(response));

        if (newUser->getRole() == 1) {
            setForemanForTeam(newUser->getTeam(), newUser->getIdUser());
        }

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
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());

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
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users/" + QString::number(idUser)));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());

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

/*!
 * \brief Funzione per invocare l'API che imposta il caposquadra di un team.
 */
void UserController::setForemanForTeam(int idTeam, int idForeman)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/teams/setforeman?idTeam="
                        +QString::number(idTeam)+"&idForeman="+QString::number(idForeman)));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::newForemanSet);
}

/*!
 * \brief Slot che riceve la risposta dell'API di settaggio caposquadra.
 */
void UserController::newForemanSet()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Everything is ok.";
    } else {
        qDebug() << "error setting the foreman.";
    }

    reply->deleteLater();
}

/*!
 * \brief Funzione che esegue la chiamata API per ricevere la posizione di ogni utente.
 */
void UserController::getUsersPosition(QStringList listUsers)
{
    qDebug() << "List user received:" << listUsers.size();

    colleguesPosition.clear();
    foreach (QString stringId, listUsers) {
        getUserPosition(stringId.toInt());
    }
}

/*!
 * \brief Funzione per invocare l'API  che riceve la posizione di un utente, se operativo.
 */
void UserController::getUserPosition(int idUser)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users/"
                        +QString::number(idUser) + "/position"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::userPositionReceived);
}

/*!
 * \briefSlot che riceve la risposta dell'API della posizione dell'utente.
 */
void UserController::userPositionReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Everything is ok." << response;

        Position * position = new Position(this);
        position->fromJsonObject(QJsonDocument::fromJson(response).object());

        colleguesPosition.append(position);
        emit colleguePositionChanged();
    } else {
        qDebug() << "Error:" << response;
    }

    reply->deleteLater();
}

/*!
 * \brief  Slot che viene chiamato quando è disponibile un update della posizione.
 */
void UserController::positionReceived()
{
    qDebug() << "Position update received: " << source->lastKnownPosition();

    QGeoPositionInfo positionInfo = source->lastKnownPosition();
    if (currentUser != nullptr) {
        if (currentUser->getState() == 1) {
            QSharedPointer<Position> pos(new Position());
            pos->setLat(positionInfo.coordinate().latitude());
            pos->setLng(positionInfo.coordinate().longitude());

            setUserPosition(pos.data());
        }
    }
}

/*!
 * \brief Funzione per invocare l'API che imposta la posizione dell'utente.
 */
void UserController::setUserPosition(Position *pos)
{
    QNetworkRequest request;
    request.setUrl(QUrl(helpers::Utils::getInstance().getWebServerPrefix() + "/users/"
                        + QString::number(currentUser->getIdUser()) + "/position"));
    request.setRawHeader("Authorization", helpers::Utils::getInstance().getAuthString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    QNetworkReply *reply = networkManager->post(request, pos->toJsonDocument().toJson());
    connect(reply, &QNetworkReply::finished, this, &UserController::positionUpdated);
}

/*!
 * \brief  Slot che viene chiamato per verificare la risposta alla chiamata per
 * l'update della posizione.
 */
void UserController::positionUpdated()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Position updated correctly.";
    } else {
        qDebug() << "Error updating the position to the server.";
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

QQmlListProperty<User> UserController::getAllUsers()
{
    return QQmlListProperty<accountManagement::User>(this, &allUsers);
}

QQmlListProperty<Position> UserController::getColleguePosition()
{
    return QQmlListProperty<accountManagement::Position>(this, &colleguesPosition);
}

void UserController::resetUser()
{
    if (currentUser != nullptr) {
        delete currentUser;
        currentUser = nullptr;
    }
}

}
