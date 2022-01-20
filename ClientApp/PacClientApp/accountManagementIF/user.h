#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

namespace accountmanagementIF {

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername CONSTANT)
    Q_PROPERTY(int state READ getState CONSTANT)
public:
    explicit User(QString jsonString, QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonDocument(QJsonDocument jsonDocument);

    QString getUsername();
    void setUsername(QString newUsername);

    int getState();
    Q_INVOKABLE void setState(QString newState);

    const QString getName() const;
    void setName(const QString newName);

    const QString getSurname() const;
    void setSurname(const QString newSurname);

    const QString getCf() const;
    void setCf(const QString newCf);

    const QString getAddress() const;
    void setAddress(const QString newAddress);

    const QString getCellnumber() const;
    void setCellnumber(const QString newCellnumber);

    const QString getSex() const;
    void setSex(const QString newSex);

    const QString getEmail() const;
    void setEmail(const QString newEmail);

    int getTeam() const;
    void setTeam(int newTeam);

    const QString getRole() const;
    void setRole(const QString newRole);

signals:

private:
    QString username;
    QString name;
    QString surname;
    QString cf;
    QString address;
    QString cellnumber;
    QString sex;
    QString email;
    int team;
    QString role;
    QString state;

};

}

#endif // USER_H
