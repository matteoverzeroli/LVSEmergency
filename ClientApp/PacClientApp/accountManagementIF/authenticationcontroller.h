#ifndef AUTHENTICATIONCONTROLLER_H
#define AUTHENTICATIONCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QnetworkReply>

namespace accountmanagementIF {

class AuthenticationController : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationController(QNetworkAccessManager *networkManager, QObject *parent = nullptr);

    Q_INVOKABLE void login(QString username, QString password);

signals:

private slots:
    void responseReceived();
    void errorReceived(QNetworkReply::NetworkError code);
    void sslErrors(const QList<QSslError> &errors);
private:
    QNetworkAccessManager *networkManager {nullptr};

};

}

#endif // AUTHENTICATIONCONTROLLER_H
