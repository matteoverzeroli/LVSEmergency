#include "utils.h"

#include <QSettings>

namespace helpers {


/*!
 * \brief Metodo statico per la generazione della stringa di autenticazione.
 */
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

}
