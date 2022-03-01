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
    QSettings settings;
    settings.beginGroup("IPAddress");
    QString prefix = settings.value("ip").toString();
    settings.endGroup();

    if (prefix.isEmpty())
        prefix = "localhost";

    if (1)
        return QString("https://lvsemergency-lvsemergency-webserver.azuremicroservices.io");
    else if (1)
        return QString("http://" + prefix + ":8080");
}

}
