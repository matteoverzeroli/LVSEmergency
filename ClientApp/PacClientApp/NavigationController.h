#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

/*!
 * \brief Classe per la navigazione nelle schermate.
 */

class NavigationController : public QObject
{
    Q_OBJECT

public:
    explicit NavigationController(QObject* parent = nullptr) : QObject(parent){

    }


signals:
    void goDashboardView();

};


#endif // NAVIGATIONCONTROLLER_H
