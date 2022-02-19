#include "utils.h"

#include <QSettings>

namespace helpers {

QByteArray Utils::getAuthString()
{
    QString username;
    QString password;
    QString authString;

    QSettings settings;
    settings.beginGroup("Credentials");
    username = settings.value("username").toString();
    password = settings.value("password").toString();
    settings.endGroup();

    QByteArray base64 = QByteArray(QString(username + ":" + password).toUtf8());

    authString = "Basic " + QString(base64.toBase64());

    return authString.toUtf8();
}

/*!
 * \brief Ritorna il prefisso della stringa da usare a seconda che si stia lavorando
 * con Spring boot in locale o in Cloud
 */
QString Utils::getWebServerPrefix()
{
    if (0)
        return QString("https://progetto-pac-lvsemergency-2021-pacserverweb.azuremicroservices.io");
    else if (1)
        return QString("http://192.168.1.18:8080");
    else
        return QString("http://localhost:8080");
}

}
