import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Item {



    Pane {
        anchors.centerIn: parent

        Material.elevation: 6

        contentWidth: formColumn.implicitWidth
        contentHeight: formColumn.implicitHeight

        Column {
            id: formColumn
            spacing: 48

            Row {
                spacing: 16

                Label {
                    id: userName
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Username:")
                }


                TextField {
                    placeholderText: qsTr("Username")
                }
            }

            Row {
                spacing: 16

                Label {
                    id: password
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Password:")
                }

                TextField {
                    placeholderText: qsTr("Password")
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Login")

                highlighted: true
                Material.accent: Material.Green

                onClicked: {
                    masterController.ui_authenticationController.login("Pippo", "Pluto")
                    console.log("Login clicked!")
                }
            }
        }
    }

}
