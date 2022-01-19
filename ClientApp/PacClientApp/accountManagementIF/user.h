#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

namespace accountmanagementIF {

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString jsonString, QObject *parent = nullptr);

    QJsonDocument toJsonDocument();
    void fromJsonDocument(QJsonDocument jsonDocument);


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
