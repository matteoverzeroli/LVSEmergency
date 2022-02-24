import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import "../assets"

Item {


    MouseArea {
        anchors {
            top: parent.top
            right:parent.right
        }

        height: 30
        width: 30



        onClicked: {
            ip.visible = true
        }
    }

    RoundPane {
        anchors.centerIn: parent

        Material.elevation: 6
        radius: 6

        contentWidth: formColumn.implicitWidth
        contentHeight: formColumn.implicitHeight

        Column {
            id: formColumn
            spacing: 40

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 150
                color: "transparent"


                AnimatedImage { id: animation;
                    source: "qrc:/assets/LVSEmergencyBIG.gif";
                    x: 10
                    width: 200;
                    height: 200
                    horizontalAlignment: Image.AlignHCenter
                }
            }

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

                Rectangle {
                    id: spacer
                    height: 8
                    width: parent.width
                    color: "transparent"

                    Label {
                        id: errorLabel
                        text: qsTr("Username e/o password errati!")
                        color: "red"
                        anchors.fill: spacer
                        anchors.horizontalCenter: spacer.horizontalCenter

                        visible: masterController.ui_userController.authError
                    }
                }
            }


            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Login")

                highlighted: true

                onClicked: {
                    masterController.ui_userController.login(userNameField.text, passwordField.text)
                    console.log("Login clicked!")
                }
            }
        }
    }

    Row {
        id: ip
        visible: false
        width: parent.width
        anchors.top: parent.top
        TextField {
            id: ipField
            placeholderText: qsTr("Indirizzo IP")
            width: parent.width * 2 / 3
        }

        Button {

            text: "Ok"

            onClicked: {
                masterController.setIpAddress(ipField.text)
                ip.visible = false
                width: parent.width * 1 / 3
            }
        }
    }

}
