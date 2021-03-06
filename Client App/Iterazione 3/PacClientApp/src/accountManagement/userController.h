#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlListProperty>
#include <QGeoPositionInfoSource>

#include "./navigationcontroller.h"
#include "user.h"
#include "position.h"

namespace accountManagement {

class UserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authError READ getAuthError NOTIFY authErrorChanged)
    Q_PROPERTY(User *currentUser READ getCurrentUser NOTIFY currentUserChanged)
    Q_PROPERTY(QQmlListProperty<accountManagement::User> users READ getAllUsers NOTIFY usersChanged)
    Q_PROPERTY(QQmlListProperty<accountManagement::Position> colleguePositions
               READ getColleguePosition NOTIFY colleguePositionChanged)
public:
    explicit UserController(QNetworkAccessManager *networkManager,
                            NavigationController *navigationController, QObject *parent = nullptr);
    ~UserController() override;

    Q_INVOKABLE void login(QString username, QString password);
    Q_INVOKABLE void modifyUser();
    Q_INVOKABLE void addUser(QString userName, QString name, QString surname,
                             QString password, QString cf, QString address,
                             QString cellNumber, QString email, int role, int idTeam, QString sex);
    Q_INVOKABLE void getUsers();
    Q_INVOKABLE void deleteUser(int idUser);
    Q_INVOKABLE void getUsersPosition(QStringList listUsers);
    Q_INVOKABLE void getUserPosition(int idUser);
    Q_INVOKABLE void resetUser();
    void setForemanForTeam(int idTeam, int idForeman);
    void setUserPosition(Position *pos);

    bool getAuthError();
    User *getCurrentUser();

    QQmlListProperty<accountManagement::User> getAllUsers();
    QQmlListProperty<accountManagement::Position> getColleguePosition();

signals:
    void authErrorChanged(bool );
    void currentUserChanged(accountManagement::User *);
    void userAddedWithSuccess();
    void errorOnAddingNewUser(QString message);
    void usersChanged(QQmlListProperty<accountManagement::User>);
    void userDeletedWithSuccess();
    void errorWhileDeletingUser();
    void colleguePositionChanged();


private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);
    void userModified();
    void userAdded();
    void allUsersReceived();
    void userDeleted();
    void newForemanSet();
    void userPositionReceived();
    void positionUpdated();
    void positionReceived();

private:
    QNetworkAccessManager *networkManager {nullptr};
    NavigationController *navigationController {nullptr};
    User *currentUser {nullptr};
    QList<User *> allUsers;
    QList<Position *> colleguesPosition;
    QGeoPositionInfoSource *source {nullptr};


    bool authenticationError {false};
};

}

#endif // USERCONTROLLER_H
