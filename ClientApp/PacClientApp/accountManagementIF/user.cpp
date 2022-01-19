#include "user.h"

#include <QSettings>

namespace accountmanagementIF {

User::User(QString jsonString, QObject *parent)
    : QObject{parent}
{
    fromJsonDocument(QJsonDocument::fromJson(jsonString.toUtf8()));
}

QJsonDocument User::toJsonDocument()
{
    QString password = "";
    QSettings settings;
    settings.beginGroup("Credentials");
    password = settings.value("password").toString();
    settings.endGroup();

    QJsonObject userObject;
    userObject.insert("username", username);
    userObject.insert("name", name);
    userObject.insert("surname", surname);
    userObject.insert("cf", cf);
    userObject.insert("address", address);
    userObject.insert("cellnumber", cellnumber);
    userObject.insert("sex", sex);
    userObject.insert("email", email);
    userObject.insert("team", team);
    userObject.insert("role", role);
    userObject.insert("state", state);
    userObject.insert("password", password);

    return QJsonDocument(userObject);
}

void User::fromJsonDocument(QJsonDocument jsonDocument)
{
    QJsonObject userObject = jsonDocument.object();
    username = userObject.value("username").toString();
    name = userObject.value("name").toString();
    surname = userObject.value("surname").toString();
    cf = userObject.value("cf").toString();
    address = userObject.value("address").toString();
    cellnumber = userObject.value("cellnumber").toString();
    sex = userObject.value("sex").toString();
    email = userObject.value("email").toString();
    team = userObject.value("team").toInt();
    role = userObject.value("role").toString();
    state = userObject.value("state").toString();
}



}
