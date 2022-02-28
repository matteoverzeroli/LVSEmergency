#ifndef TESTENTITYIF_H
#define TESTENTITYIF_H

#include <QObject>
#include <QtTest/QtTest>
#include "../src/accountManagementIF/user.h"
#include "../src/teamManagementIF/team.h"
#include "../src/areaInformationManagementIF/area.h"

class TestEntityIF : public QObject
{
    Q_OBJECT

private slots:
    void testUserFromJson();
    void testTeamFromJson();
    void testAreaFromJson();
};

#endif // TESTENTITYIF_H
