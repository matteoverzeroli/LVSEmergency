import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Page {
    id: window

    Action {
        id: navigateBackAction
        icon.name: stackView.depth > 1 ? "back" : "drawer"
        onTriggered: {
            if (stackView.depth > 1) {
                stackView.pop()
                listView.currentIndex = -1
            } else {
                drawer.open()
            }
        }
    }

    Action {
        id: optionsMenuAction
        icon.name: "menu"
        onTriggered: optionsMenu.open()
    }

    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                action: navigateBackAction
            }

            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : "LVSEmergency"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                action: optionsMenuAction

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    Action {
                        text: "Logout"
                        onTriggered: {
                            masterController.ui_navigationController.needLoginForm();
                        }
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        interactive: stackView.depth === 1

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: listView.width
                text: model.title
                visible: model.user >= masterController.ui_userController.currentUser.role
                height: visible == true ? implicitHeight : 0
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()

                    if (model.source === "qrc:/views/InserisciUtente.qml") {
                        masterController.ui_teamController.getTeams()
                    } else if (model.source === "qrc:/views/CreaSquadra.qml") {
                        masterController.ui_areaController.getAreas()
                    } else if (model.source === "qrc:/views/Impostazioni.qml") {
                        masterController.ui_teamController.getTeam(
                                    masterController.ui_userController.currentUser.idTeam)
                    } else if (model.source === "qrc:/views/CancellaUtente.qml") {
                        masterController.ui_userController.getUsers()
                    }
                }
            }

            model: ListModel {
                ListElement { title: "Inserisci Utente"; user: 0 ; source: "qrc:/views/InserisciUtente.qml" }
                ListElement { title: "Cancella Utente"; user: 0 ; source: "qrc:/views/CancellaUtente.qml" }
                ListElement { title: "Crea Squadra"; user: 0 ; source: "qrc:/views/CreaSquadra.qml" }
                ListElement { title: "Impostazioni"; user: 2; source: "qrc:/views/Impostazioni.qml" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Flickable {
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

                    Label {
                        id: modifyStatus
                        width: parent.width
                        wrapMode: Label.Wrap
                        horizontalAlignment: Qt.AlignHCenter
                        text: qsTr("Clicca il pulsante per modificare lo stato di operatività.")
                    }

                    Button {
                        text: masterController.ui_userController.currentUser.state == 0 ?
                                  qsTr("Stato: inattivo") : qsTr("Stato: attivo")

                        highlighted: masterController.ui_userController.currentUser.state == 1

                        anchors.horizontalCenter: parent.horizontalCenter

                        onClicked: {
                            var stateString = masterController.ui_userController.currentUser.state == 0 ? "ACTIVE" : "INACTIVE"
                            masterController.ui_userController.currentUser.setState(stateString)
                            masterController.ui_userController.modifyUser()
                        }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar { }
        }
    }
}


