import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Flickable {
    id: flickable

    contentHeight: column.height + 20

    Connections {
        target: masterController.ui_teamController

        function onTeamAddedWithSuccess() {
            busyIndicator.running = false

            teamAddedDialog.open()
        }

        function onErrorWhileAddingTeam() {
            busyIndicator.running = false

            userErrorDialog.open()
        }
    }

    Dialog {
        id: teamAddedDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: Overlay.overlay

        modal: true
        title: "Squadra creata!"
        standardButtons: Dialog.Ok

        width: parent.width - 100

        Column {
            spacing: 20
            anchors.fill: parent
            Label {
                text: "La squadra è stata inserita con successo!"
                width: parent.width
                wrapMode: Label.Wrap
            }
        }
    }

    Dialog {
        id: userErrorDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: Overlay.overlay

        width: parent.width - 100

        modal: true
        title: "Attenzione!"
        standardButtons: Dialog.Ok

        Column {
            spacing: 20
            anchors.fill: parent
            Label {
                text: "Una squadra con questo nome è già stata creata!"
                width: parent.width
                wrapMode: Label.Wrap
            }
        }
    }


    Column {
        id: column
        width: parent.width - 40
        x: 20
        y: 20
        spacing: 16


        Rectangle {
            width: parent.width
            color: "transparent"
            height: 48

            Row {
                anchors.fill: parent
                Label {
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Nome del team:")

                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: teamNameField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Nome del team")
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }

        Rectangle {
            width: parent.width
            color: "transparent"
            height: 48

            Row {
                anchors.fill: parent
                Label {
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Area:")

                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                ComboBox {
                    id: comboArea
                    model: masterController.ui_areaController.areasAvailableList
                    height: parent.height
                    width: parent.width / 2
                }
            }
        }


        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: qsTr("Crea Squadra")

                highlighted: true

                onClicked: {
                    console.log("Inserendo la squadra!")

                    if (verifyFields()) {
                        busyIndicator.running = true
                        var idArea = masterController.ui_areaController.getIdAreaByName(comboArea.currentText)

                        masterController.ui_teamController.addTeam(teamNameField.text, idArea)
                    } else {
                        fieldErrorDialog.open()
                    }

                }

                Dialog {
                    id: fieldErrorDialog

                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2
                    parent: Overlay.overlay

                    modal: true
                    title: "Attenzione!"
                    standardButtons: Dialog.Ok
                    width: parent.width - 100

                    Column {
                        spacing: 20
                        anchors.fill: parent
                        Label {
                            text: "Verificare di aver inserito correttamente tutti i campi e riprovare."
                            width: parent.width
                            wrapMode: Label.Wrap
                        }
                    }
                }

                function verifyFields () {
                    if (teamNameField.acceptableInput && teamNameField.text != ""
                            && comboArea.currentText != "")
                        return true

                    return false
                }
            }

            BusyIndicator {
                id: busyIndicator
                running: false
            }
        }



    }

    ScrollBar.vertical: ScrollBar { }
}
