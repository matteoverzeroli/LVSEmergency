import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Flickable {
    id: flickable

    contentHeight: column.height

    Column {
        id: column
        width: parent.width
        spacing: 16

        RowLayout {

            ColumnLayout {
                Label {
                    id: userName
                    height: 24
                    text: qsTr("Username:")
                }

                Label {
                    id: name
                    height: 24
                    text: qsTr("Nome:")
                }

                Label {
                    id: surname
                    height: 24
                    text: qsTr("Cognome:")
                }
            }

            ColumnLayout {
                TextField {
                    id: userNameField
                    height: 24
                    width: parent.width
                    placeholderText: qsTr("Username")
                }

                TextField {
                    id: nameField
                    height: 24
                    width: parent.width
                    placeholderText: qsTr("Nome")
                }

                TextField {
                    id: surnameField
                    height: 24
                    width: parent.width
                    placeholderText: qsTr("Cognome")
                }
            }
        }
//        RowLayout {
//            spacing: 8
//            Label {
//                id: userName
//                text: qsTr("Username:")
//            }

//            TextField {
//                id: userNameField
//                width: parent.width
//                placeholderText: qsTr("Username")
//            }
//        }

//        RowLayout {
//            spacing: 8
//            Label {
//                id: name
//                text: qsTr("Nome:")
//            }

//            TextField {
//                id: nameField
//                width: parent.width
//                placeholderText: qsTr("Nome")
//            }
//        }

//        RowLayout {
//            spacing: 8
//            Label {
//                id: surname
//                text: qsTr("Cognome:")
//            }

//            TextField {
//                id: surnameField
//                width: parent.width
//                placeholderText: qsTr("Cognome")
//            }
//        }

        Rectangle {
            height: 2
            width: parent.width * 5 / 6
            radius: 5
            anchors.horizontalCenter: parent.horizontalCenter

            color: "#999999"
        }

    }


    ScrollBar.vertical: ScrollBar { }
}
