#include "authenticationcontroller.h"

#include <QDebug>


namespace accountmanagementIF {
AuthenticationController::AuthenticationController(QNetworkAccessManager *networkManager, QObject *parent)
    : QObject{parent},
      networkManager(networkManager)
{

}

/*!
 * \brief Funzione per invocare l'API che esegue il login.
 */
void AuthenticationController::login(QString username, QString password)
{
    qDebug() << "Calling the slot correclty";
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/admin"));
//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &AuthenticationController::responseReceived);
    connect(reply, &QNetworkReply::errorOccurred, this, &AuthenticationController::errorReceived);
    connect(reply, &QNetworkReply::sslErrors, this, &AuthenticationController::sslErrors);
}

void AuthenticationController::responseReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    QByteArray response = reply->readAll();
    qDebug() << "Received something from Internet:" << QString(response) << response.size() << reply->error();


    reply->deleteLater();
}

void AuthenticationController::errorReceived(QNetworkReply::NetworkError code)
{
    qDebug() << "Some error occoured:" << code;
}

void AuthenticationController::sslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Some sslErrors occoured!";
}

}
