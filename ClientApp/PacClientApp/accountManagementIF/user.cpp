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
    userObject.insert("cellNumber", cellnumber);
    userObject.insert("sex", sex);
    userObject.insert("email", email);
    userObject.insert("idTeam", team);
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
    cellnumber = userObject.value("cellNumber").toString();
    sex = userObject.value("sex").toString();
    email = userObject.value("email").toString();
    team = userObject.value("idTeam").toInt();
    role = userObject.value("role").toString();
    state = userObject.value("state").toString();
}

QString User::getUsername()
{
    return username;
}

void User::setUsername(QString newUsername)
{
    username = newUsername;
}

int User::getState()
{
    if (state == "INACTIVE") return 0;
    else return 1;
}

void User::setState(QString newState)
{
    state = newState;
}

const QString User::getName() const
{
    return name;
}

void User::setName(const QString newName)
{
    name = newName;
}

const QString User::getSurname() const
{
    return surname;
}

void User::setSurname(const QString newSurname)
{
    surname = newSurname;
}

const QString User::getCf() const
{
    return cf;
}

void User::setCf(const QString newCf)
{
    cf = newCf;
}

const QString User::getAddress() const
{
    return address;
}

void User::setAddress(const QString newAddress)
{
    address = newAddress;
}

const QString User::getCellnumber() const
{
    return cellnumber;
}

void User::setCellnumber(const QString newCellnumber)
{
    cellnumber = newCellnumber;
}

const QString User::getSex() const
{
    return sex;
}

void User::setSex(const QString newSex)
{
    sex = newSex;
}

const QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString newEmail)
{
    email = newEmail;
}

int User::getTeam() const
{
    return team;
}

void User::setTeam(int newTeam)
{
    team = newTeam;
}

const QString User::getRole() const
{
    return role;
}

void User::setRole(const QString newRole)
{
    role = newRole;
}



}
