#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlListProperty>

#include "./navigationcontroller.h"
#include "user.h"

namespace accountmanagementIF {

class UserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authError READ getAuthError NOTIFY authErrorChanged)
    Q_PROPERTY(User *currentUser READ getCurrentUser NOTIFY currentUserChanged)
    Q_PROPERTY(QQmlListProperty<accountmanagementIF::User> users READ getAllUsers NOTIFY usersChanged)
public:
    explicit UserController(QNetworkAccessManager *networkManager,
                            NavigationController *navigationController, QObject *parent = nullptr);

    Q_INVOKABLE void login(QString username, QString password);
    Q_INVOKABLE void modifyUser();
    Q_INVOKABLE void addUser(QString userName, QString name, QString surname,
                             QString password, QString cf, QString address,
                             QString cellNumber, QString email, int role, int idTeam, QString sex);
    Q_INVOKABLE void getUsers();
    Q_INVOKABLE void deleteUser(int idUser);

    bool getAuthError();
    User *getCurrentUser();

    QQmlListProperty<accountmanagementIF::User> getAllUsers();

signals:
    void authErrorChanged(bool );
    void currentUserChanged(accountmanagementIF::User *);
    void userAddedWithSuccess();
    void errorOnAddingNewUser();
    void usersChanged(QQmlListProperty<accountmanagementIF::User>);
    void userDeletedWithSuccess();
    void errorWhileDeletingUser();

private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);

    void userModified();
    void userAdded();
    void allUsersReceived();
    void userDeleted();
private:
    QNetworkAccessManager *networkManager {nullptr};
    NavigationController *navigationController {nullptr};
    User *currentUser {nullptr};
    QList<User *> allUsers;

    bool authenticationError {false};
};

}

#endif // USERCONTROLLER_H
