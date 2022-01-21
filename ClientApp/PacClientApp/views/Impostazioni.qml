import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Flickable {
    id: flickable

    contentHeight: pane.height

    Pane {
        id: pane
        width: flickable.width
        height: flickable.height

        Column {
            id: column
            spacing: 24
            width: parent.width

            Label {
                id: username
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Qt.AlignHCenter
                text: "Bentornato " +
                      masterController.ui_userController.currentUser.username
                      + "!"
                font.bold: true
                font.pointSize: 16
            }

            Label {
                id: info
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Qt.AlignHCenter
                text: "Ecco alcune informazioni su di te:"

                font.pointSize: 12
            }

            RoundPane {
                Material.elevation: 6
                radius: 6
                Material.background: "#F2CB05"
                anchors.horizontalCenter: parent.horizontalCenter

                Column {
                    id: columnInfo
                    spacing: 8

                    Label {
                        id: name
                        text: qsTr("Nome: ") + masterController.ui_userController.currentUser.name
                    }

                    Label {
                        id: surname
                        text: qsTr("Cognome: ") + masterController.ui_userController.currentUser.username
                    }

                    Label {
                        id: cf
                        text: qsTr("Codice Fiscale: ") + masterController.ui_userController.currentUser.cf
                    }

                    Label {
                        id: ruolo
                        text: qsTr("Ruolo: ") + getRole(masterController.ui_userController.currentUser.role)

                        function getRole(role) {
                            if (role == 0) return "Amministratore"
                            if (role == 1) return "Caposquadra"
                            if (role == 2) return "Volontario"
                        }
                    }
                }
            }

            Rectangle {
                height: 2
                width: parent.width * 5 / 6
                radius: 5
                anchors.horizontalCenter: parent.horizontalCenter

                color: "#999999"
            }

        }
    }

    ScrollBar.vertical: ScrollBar { }
}
