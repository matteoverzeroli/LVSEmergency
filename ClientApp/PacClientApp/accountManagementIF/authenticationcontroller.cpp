#include "authenticationcontroller.h"

#include <QDebug>
#include <QSettings>
#include <QJsonDocument>

#include "./helpers/utils.h"


namespace accountmanagementIF {
AuthenticationController::AuthenticationController(QNetworkAccessManager *networkManager,
                                                   NavigationController *navigationController,
                                                   QObject *parent)
    : QObject{parent},
      navigationController(navigationController),
      networkManager(networkManager)
{

}

/*!
 * \brief Funzione per invocare l'API che esegue il login.
 * \details Vengono salvate nel file settings le credenziali.
 * In questo modo possono essere utilizzate per altre API.
 */
void AuthenticationController::login(QString username, QString password)
{
    QSettings settings;
    settings.beginGroup("Credentials");
    settings.setValue("username", username);
    settings.setValue("password", password);
    settings.endGroup();

    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8080/admin"));
    request.setRawHeader("Authorization", helpers::Utils::getAuthString());

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

    // todo: gestire la risposta del sistema. Una soluzione semplice potrebbe essere quella di creare una classe.
    /* Se creiamo una classe e gli diamo in pasto il JSON, la classe avrà un metodo che estrae tutto ciò che è
     * contenuto all'interno dell'applicazione. Dopo di che a noi non rimane altre che accedere ai campi. Per
     * risposte singole è più semplice, per risposte complesse (tipo diversi tipi di allarme) è più difficile.
     * In quel caso si potrebbero creare dei parser che restituiscono una lista di allarmi.
     * Questo discorso non vale molto qui dato che ci serve solo sapere l'ID e il tipo di utente (andrei a salvare
     * entrambi nel settings così ci possiamo accedere da dove vogliamo.
     */

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Everything worked well";

        // https://forum.qt.io/topic/91346/how-to-get-a-json-value-from-an-api-and-display-it-in-a-gui/4

        navigationController->goDashboardView();
    } else if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
        qDebug() << "Authentication required";
    }

    reply->deleteLater();
}

void AuthenticationController::errorReceived(QNetworkReply::NetworkError code)
{
    qDebug() << "Some error occoured:" << code;
}

void AuthenticationController::sslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors)
    qDebug() << "Some sslErrors occoured!";
}


}
