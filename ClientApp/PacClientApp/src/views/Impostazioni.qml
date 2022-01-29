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

        Column {
            id: column
            spacing: 24
            width: parent.width

            Label {
                id: username
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Qt.AlignHCenter
                text: "Ciao " +
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
                            if (role === 0) return "Amministratore"
                            if (role === 1) return "Caposquadra"
                            if (role === 2) return "Volontario"
                        }
                    }

                    Label {
                        id: address
                        text: qsTr("Indirizzo: ") + masterController.ui_userController.currentUser.address
                    }

                    Label {
                        id: cellNumber
                        text: qsTr("Cellulare: ") + masterController.ui_userController.currentUser.cellNumber
                    }

                    Label {
                        id: email
                        text: qsTr("Email: ") + masterController.ui_userController.currentUser.email
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

            Label {
                id: infoSquadra
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Qt.AlignHCenter
                text: checkTeamNull()

                function checkTeamNull() {
                    if (masterController.ui_teamController.currentTeam === null)
                        return "Non sei stato assegnato ad una squadra."

                    return "Ecco alcune informazioni sulla tua squadra:"
                }

                font.pointSize: 12
            }

            RoundPane {
                Material.elevation: 6
                radius: 6
                Material.background: "#F2CB05"
                anchors.horizontalCenter: parent.horizontalCenter

                visible: masterController.ui_teamController.currentTeam === null ? false : true

                Column {
                    id: columnInfoSquadra
                    spacing: 8

                    Label {
                        id: nameTeam
                        text: qsTr("Nome squadra: ") + masterController.ui_teamController.currentTeam.teamName
                    }

                    Label {
                        id: teamMembersNum
                        text: qsTr("Membri della squadra: ") + masterController.ui_teamController.currentTeam.users.length
                    }

                    Label {
                        id: areaName
                        text: qsTr("Area: ") + masterController.ui_teamController.currentTeam.area.areaName
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

            Label {
                id: infoTeam
                width: parent.width
                wrapMode: Label.Wrap
                horizontalAlignment: Qt.AlignHCenter
                text: checkNoMemberNull()

                font.pointSize: 12

                function checkNoMemberNull() {
                    if (masterController.ui_teamController.currentTeam.users.length === 1)
                        return "Al momento non hai compagni di squadra."

                    return "Ecco i tuoi compagni di squadra:"
                }
            }

            Column {
                spacing: 16
                anchors.horizontalCenter: parent.horizontalCenter

                Repeater {
                    model: masterController.ui_teamController.currentTeam.users

                    RoundPane {
                        Material.elevation: 6
                        radius: 6
                        Material.background: "#F2CB05"

                        anchors.horizontalCenter: parent.horizontalCenter

                        visible: model.idUser !==
                                 masterController.ui_userController.currentUser.idUser


                        Column {
                            Label {
                                text: qsTr("Nome: " + model.name)
                            }

                            Label {
                                text: qsTr("Cognome: " + model.surname)
                            }

                            Label {
                                text: qsTr("Cellulare: " + model.cellNumber)
                            }

                            Label {
                                text: qsTr("Email: " + model.email)
                            }

                            Label {
                                text: qsTr("Ruolo: ") + getRole(model.role)

                                font.bold: model.role === 1

                                color: model.role == 1 ? "red" : "black"

                                function getRole(role) {
                                    if (role == 0) return "Amministratore"
                                    if (role == 1) return "Caposquadra"
                                    if (role == 2) return "Volontario"
                                }
                            }
                        }
                    }
                }
            }

        }
    }

    ScrollBar.vertical: ScrollBar { }
}
