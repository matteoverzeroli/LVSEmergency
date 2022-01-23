#ifndef ENTITYIF_H
#define ENTITYIF_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

namespace helpers {

class EntityIF : public QObject
{
    Q_OBJECT

public:
    virtual QJsonDocument toJsonDocument() = 0;
    virtual void fromJsonObject(QJsonObject) = 0;

};

}


#endif // ENTITYIF_H
