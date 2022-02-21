#ifndef UTILS_H
#define UTILS_H

#include <QObject>


namespace helpers {

class Utils : public QObject
{
    Q_OBJECT
public:
    QByteArray getAuthString();
    QString getWebServerPrefix();

    static Utils& getInstance() {
        static Utils instance;
        return instance;
    }

private:
    Utils(){}


};

}

#endif // UTILS_H
