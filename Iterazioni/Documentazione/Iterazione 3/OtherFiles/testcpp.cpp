void TestEntityIF::testAprsDataFromJson()
{
    QString jsonString = "{\"name\":\"cw6134\",\"time\":\"28-01-2022 01:10:13\",\"temperature\":0.0,"
                         "\"pressure\":1024.2,\"humidity\":95,\"windDirection\":180.0,\"windSpeed\":0.4,"
                         "\"windGust\":1.3,\"rainOneHour\":0.0,\"rainDay\":0.0,\"rainMidNight\":0.0,\"luminosity\":null}";

    areaInformationManagementIF::AprsData *aprs = new areaInformationManagementIF::AprsData();
    aprs->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(aprs->getName() == "cw6134");
    QVERIFY(aprs->getDate() == "28-01-2022 01:10:13");
    QVERIFY(qFuzzyCompare(aprs->getPressure(), 1024.2f));
    QVERIFY(qFuzzyCompare(aprs->getTemperature(), 0.0f));
    QVERIFY(qFuzzyCompare(aprs->getWindDirection(), 180.0f));
    QVERIFY(qFuzzyCompare(aprs->getWindSpeed(), 0.4f));
    QVERIFY(qFuzzyCompare(aprs->getWindGust(), 1.3f));
    QVERIFY(aprs->getHumidity() == 95);
    QVERIFY(aprs->getRainOneHour() == 0.0);
    QVERIFY(aprs->getRainDay() == 0.0);
    QVERIFY(aprs->getRainMidNight() == 0.0);
}

void TestEntityIF::testAlarmFromJson()
{
    QString jsonString = "{\"idAlarm\":4,\"time\":\"26-01-2022 18:12:24\",\"type\":"
                         "\"FROST\",\"color\":\"GREEN\",\"idArea\":1,\"description\":\"no description\"}";

    areaInformationManagementIF::Alarm *alarm = new areaInformationManagementIF::Alarm();
    alarm->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(alarm->getIdArea() == 1);
    QVERIFY(alarm->getDate() == "26-01-2022 18:12:24");
    QVERIFY(alarm->getColor() == "GREEN");
    QVERIFY(alarm->getType() == "FROST");
    QVERIFY(alarm->getDescription() == "no description");
}