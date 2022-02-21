
void TestEntityIF::testPositionFromJson()
{
    QString jsonString = "{\"idPosition\": 117,\"lat\": 45.67466793823242,\"lng\": 9.802000190734862,"
                         "\"time\": \"20-02-2022 14:19:09\",\"idUser\": 16,\"name\": \"Matteo\",\"surname\": \"Verzeroli\"}";

    accountManagement::Position *position = new accountManagement::Position();
    position->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(position->getIdPosition() == 117);
    QVERIFY(position->getLat() == 45.67466793823242);
    QVERIFY(position->getLng() == 9.802000190734862);
    QVERIFY(position->getDate() == "20-02-2022 14:19:09");
    QVERIFY(position->getIdUser() == 16);
    QVERIFY(position->getName() == "Matteo");
    QVERIFY(position->getSurname() == "Verzeroli");
}