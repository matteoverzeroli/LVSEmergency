#include "userController.h"

#include <QDebug>


namespace accountmanagementIF {
UserController::UserController(QNetworkAccessManager *networkManager, QObject *parent)
    : QObject{parent},
      networkManager(networkManager)
{

}

/*!
 * \brief Funzione per invocare l'API che esegue il login.
 */
void UserController::login(QString username, QString password)
{
    qDebug() << "Calling the slot correclty";
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/admin"));
//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &UserController::responseReceived);
    connect(reply, &QNetworkReply::errorOccurred, this, &UserController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &UserController::sslErrors);
}

void UserController::responseReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();
    qDebug() << "Received something from Internet:" << QString(response) << response.size() << reply->error();


    reply->deleteLater();
}

void UserController::errorReceived(QNetworkReply::NetworkError code)
{
    qDebug() << "Some error occoured:" << code;
}

void UserController::sslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Some sslErrors occoured!";
}

}
