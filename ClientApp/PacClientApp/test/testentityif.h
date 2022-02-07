#ifndef TESTENTITYIF_H
#define TESTENTITYIF_H

#include <QObject>
#include <QtTest/QtTest>
#include "../src/accountManagement/user.h"
#include "../src/teamManagement/team.h"
#include "../src/areaInformationManagement/area.h"
#include "../src/areaInformationManagement/aprsdata.h"
#include "../src/areaInformationManagement/alarm.h"

class TestEntityIF : public QObject
{
    Q_OBJECT

private slots:
    void testUserFromJson();
    void testTeamFromJson();
    void testAreaFromJson();
    void testAprsDataFromJson();
    void testAlarmFromJson();
};

#endif // TESTENTITYIF_H
