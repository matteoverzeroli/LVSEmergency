#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "mastercontroller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    // faccio conoscere al QML le classi che può utilizzare registrando il loro tipo
    qmlRegisterUncreatableType<MasterController>("PacApp", 1, 0, "MasterController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<NavigationController>("PacApp", 1, 0, "NavigationController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<accountmanagementIF::AuthenticationController>("PacApp", 1, 0, "AuthenticationController", "This class cannot be created by QML.");


    MasterController masterController;

    engine.rootContext()->setContextProperty("masterController", &masterController);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}