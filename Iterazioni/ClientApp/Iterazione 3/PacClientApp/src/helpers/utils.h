#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace helpers {

class Utils : public QObject
{
    Q_OBJECT
public:
    static QByteArray getAuthString();
    static QString getWebServerPrefix();

signals:

};

}

#endif // UTILS_H
