#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "./navigationcontroller.h"
#include "user.h"

namespace accountmanagementIF {

class UserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authError READ getAuthError NOTIFY authErrorChanged)
    Q_PROPERTY(User *currentUser READ getCurrentUser NOTIFY currentUserChanged)
public:
    explicit UserController(QNetworkAccessManager *networkManager,
                            NavigationController *navigationController, QObject *parent = nullptr);

    Q_INVOKABLE void login(QString username, QString password);
    Q_INVOKABLE void modifyUser();

    bool getAuthError();
    User *getCurrentUser();

signals:
    void authErrorChanged(bool );
    void currentUserChanged(User *);

private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);

    void userModified();
private:
    QNetworkAccessManager *networkManager {nullptr};
    NavigationController *navigationController {nullptr};
    User *currentUser {nullptr};

    bool authenticationError {false};


};

}

#endif // USERCONTROLLER_H
