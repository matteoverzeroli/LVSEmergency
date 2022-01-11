#ifndef AUTHENTICATIONCONTROLLER_H
#define AUTHENTICATIONCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "./navigationcontroller.h"

namespace accountmanagementIF {

class AuthenticationController : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationController(QNetworkAccessManager *networkManager,
                                      NavigationController *navigationController,
                                      QObject *parent = nullptr);

    Q_INVOKABLE void login(QString username, QString password);

signals:

private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);

private:
    NavigationController *navigationController {nullptr};
    QNetworkAccessManager *networkManager {nullptr};

};

}

#endif // AUTHENTICATIONCONTROLLER_H
