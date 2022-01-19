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
    int getState();

    // aggiungere getters and setters

    //aggiungere signals modifica dei campi

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
