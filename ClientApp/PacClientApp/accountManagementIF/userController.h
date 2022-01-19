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
public:
    explicit UserController(QNetworkAccessManager *networkManager,
                            NavigationController *navigationController, QObject *parent = nullptr);

    Q_INVOKABLE void login(QString username, QString password);

    bool getAuthError();

signals:
    void authErrorChanged(bool );

private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);

private:
    QNetworkAccessManager *networkManager {nullptr};
    NavigationController *navigationController {nullptr};
    User *currentUser {nullptr};

    bool authenticationError {false};


};

}

#endif // USERCONTROLLER_H
