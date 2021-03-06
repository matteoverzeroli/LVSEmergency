QT += positioning quick quickcontrols2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        accountManagement/position.cpp \
        accountManagement/user.cpp \
        accountManagement/userController.cpp \
        areaInformationManagement/alarm.cpp \
        areaInformationManagement/aprsdata.cpp \
        areaInformationManagement/area.cpp \
        areaInformationManagement/areacontroller.cpp \
        helpers/radialbar.cpp \
        helpers/utils.cpp \
        main.cpp \
        mastercontroller.cpp \
        teamManagement/team.cpp \
        teamManagement/teamcontroller.cpp

HEADERS += \
    accountManagement/position.h \
    accountManagement/user.h \
    accountManagement/userController.h \
    areaInformationManagement/alarm.h \
    areaInformationManagement/aprsdata.h \
    areaInformationManagement/area.h \
    areaInformationManagement/areacontroller.h \
    helpers/entityif.h \
    helpers/radialbar.h \
    helpers/utils.h \
    navigationcontroller.h \
    mastercontroller.h \
    teamManagement/team.h \
    teamManagement/teamcontroller.h

RESOURCES += \
        qml.qrc \
        qtquickcontrols2.conf \
        icons/gallery/index.theme \
        icons/gallery/20x20/back.png \
        icons/gallery/20x20/drawer.png \
        icons/gallery/20x20/menu.png \
        icons/gallery/20x20@2/back.png \
        icons/gallery/20x20@2/drawer.png \
        icons/gallery/20x20@2/menu.png \
        icons/gallery/20x20@3/back.png \
        icons/gallery/20x20@3/drawer.png \
        icons/gallery/20x20@3/menu.png \
        icons/gallery/20x20@4/back.png \
        icons/gallery/20x20@4/drawer.png \
        icons/gallery/20x20@4/menu.png \
        images/arrow.png \
        images/arrow@2x.png \
        images/arrow@3x.png \
        images/arrow@4x.png \
        images/arrows.png \
        images/arrows@2x.png \
        images/arrows@3x.png \
        images/arrows@4x.png \
        images/qt-logo.png \
        images/qt-logo@2x.png \
        images/qt-logo@3x.png \
        images/qt-logo@4x.png

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android: include(C:/Users/Davide/AppData/Local/Android/Sdk/android_openssl/openssl.pri)

win32:RC_ICONS += C:/Users/Davide/Documents/Progetto-PAC/ClientApp/Iterazione3/PacClientApp/src/assets/LVSEmergency.ico

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android






