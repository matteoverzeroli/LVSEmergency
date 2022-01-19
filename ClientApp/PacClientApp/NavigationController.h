#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>
#include <QSettings>

class NavigationController : public QObject
{
    Q_OBJECT

public:
    explicit NavigationController(QObject* parent = nullptr) : QObject(parent){}

    void needDashboardView() {
        emit goDashboardView();
    }

    Q_INVOKABLE void needLoginForm() {
        QSettings settings;
        settings.beginGroup("Credentials");
        settings.setValue("username", "");
        settings.setValue("password", "");
        settings.endGroup();

        emit goLoginForm();
    }

signals:
    void goDashboardView();
    void goLoginForm();


};


#endif // NAVIGATIONCONTROLLER_H
