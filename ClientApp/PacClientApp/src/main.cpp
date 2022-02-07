#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QIcon>

#include "mastercontroller.h"
#include "./helpers/radialbar.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QCoreApplication::setOrganizationName("LVSEmergency");
    QCoreApplication::setApplicationName("LVSEmergency");

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    QIcon::setThemeName("gallery");


    MasterController masterController;

    QQmlApplicationEngine engine;

    // faccio conoscere al QML le classi che può utilizzare registrando il loro tipo
    qmlRegisterUncreatableType<MasterController>("PacApp", 1, 0, "MasterController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<NavigationController>("PacApp", 1, 0, "NavigationController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<accountManagement::UserController>("PacApp", 1, 0, "UserController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<accountManagement::User>("PacApp", 1, 0, "User", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<teamManagement::TeamController>("PacApp", 1, 0, "TeamController", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<teamManagement::Team>("PacApp", 1, 0, "Team", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<areaInformationManagement::Area>("PacApp", 1, 0, "Area", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<areaInformationManagement::AprsData>("PacApp", 1, 0, "AprsData", "This class cannot be created by QML.");
    qmlRegisterUncreatableType<areaInformationManagement::Alarm>("PacApp", 1, 0, "Alarm", "This class cannot be created by QML.");
    qmlRegisterType<helpers::RadialBar>("CustomControls", 1, 0, "RadialBar");

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
