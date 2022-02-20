QT += quick quickcontrols2 testlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/accountManagement/position.cpp \
    ../src/accountManagement/user.cpp \
    ../src/areaInformationManagement/alarm.cpp \
    ../src/areaInformationManagement/aprsdata.cpp \
    ../src/areaInformationManagement/area.cpp \
    ../src/teamManagement/team.cpp \
    testentityif.cpp

HEADERS += \
    ../src/accountManagement/position.h \
    ../src/accountManagement/user.h \
    ../src/areaInformationManagement/alarm.h \
    ../src/areaInformationManagement/aprsdata.h \
    ../src/areaInformationManagement/area.h \
    ../src/helpers/entityif.h \
    ../src/teamManagement/team.h \
    testentityif.h


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





