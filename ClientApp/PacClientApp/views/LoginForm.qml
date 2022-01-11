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
                    id: userNameField
                    placeholderText: qsTr("Username")
                }
            }

            Row {


                Column {
                    spacing: 8
                    Row {
                        spacing: 16
                        Label {
                            id: password
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr("Password:")
                        }

                        TextField {
                            id: passwordField
                            placeholderText: qsTr("Password")
                            echoMode: checkShowPassword.checked ? TextField.Normal : TextField.Password
                        }
                    }

                    CheckBox {
                        id: checkShowPassword
                        text: qsTr("Mostra password")
                        checked: false
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            Rectangle {
                id: spacer
                height: 16
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Login")

                highlighted: true
                Material.accent: Material.Green

                onClicked: {
                    masterController.ui_authenticationController.login(userNameField.text, passwordField.text)
                    console.log("Login clicked!")
                }
            }
        }
    }

}
