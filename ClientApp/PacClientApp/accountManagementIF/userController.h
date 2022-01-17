#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace accountmanagementIF {

class UserController : public QObject
{
    Q_OBJECT
public:
    explicit UserController(QNetworkAccessManager *networkManager, QObject *parent = nullptr);

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

#endif // USERCONTROLLER_H
