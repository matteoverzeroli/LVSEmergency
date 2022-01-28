import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Item {

    Connections {
        target: masterController.ui_areaController

        function onFrogorfrostAlarmChanged() {
            if (masterController.ui_areaController.frogorfrostAlarm === null) {
                dataErrorDialog.open()
            } else {
                loading.running = false
                flickable.visible = true
            }
        }

    }

    BusyIndicator {
        id: loading
        running: true
        anchors.centerIn: parent
    }

    Flickable {
        id: flickable
        anchors.fill: parent

        visible: false

        contentHeight: column.height + 20

        Dialog {
            id: teamAddedDialog

            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            parent: Overlay.overlay

            modal: true
            title: "Squadra creata!"
            standardButtons: Dialog.Ok

            Column {
                spacing: 20
                anchors.fill: parent
                Label {
                    text: "La squadra è stata inserita con successo!"
                    wrapMode: Label.Wrap
                }
            }
        }

        Dialog {
            id: dataErrorDialog

            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            parent: Overlay.overlay

            modal: true
            title: "Attenzione!"
            standardButtons: Dialog.Ok

            Column {
                spacing: 20
                anchors.fill: parent
                Label {
                    text: "Errore durante la ricezione dei dati!"
                    wrapMode: Label.Wrap
                }
            }
        }

        Column {
            id: column
            width: parent.width - 40
            x: 20
            spacing: 16

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
                text: "Ecco gli allarmi presenti nella tua area:"

                font.pointSize: 12
            }

            RoundPane {
                Material.elevation: 6
                radius: 6
                anchors.horizontalCenter: parent.horizontalCenter

                width: parent.width * 4 / 5

                Material.background: getColor()
                Material.foreground: getForeground()

                function getColor() {
                    var color = masterController.ui_areaController.frogorfrostAlarm.color
                    if (color === "NONE")
                        return "#D9D9D9"
                    if (color === "WHITE")
                        return "white"
                    if (color === "GREEN")
                        return "green"
                    if (color === "ORANGE")
                        return "#F29F05"
                    if (color === "RED")
                        return "red"
                }

                function getForeground(){
                    var color = masterController.ui_areaController.frogorfrostAlarm.color
                    if (color === "NONE" || color === "WHITE")
                        return "#000000"

                    return "#FFFFFF"
                }

                Column {
                    spacing: 8
                    width: parent.width

                    Label {
                        id: alarmDate
                        text: masterController.ui_areaController.frogorfrostAlarm.date
                        width: parent.width

                        horizontalAlignment: Qt.AlignLeft
                        font.pointSize: 10
                    }

                    Label {
                        id: alarmType
                        text: getText()
                        width: parent.width

                        horizontalAlignment: Qt.AlignHCenter
                        font.bold: true
                        font.pointSize: 16

                        function getText() {
                            var type = masterController.ui_areaController.frogorfrostAlarm.type
                            if (type === "FOG")
                                return "Nebbia"
                            if (type === "FROST")
                                return "Brina"
                        }
                    }


                    Label {
                        text: masterController.ui_areaController.frogorfrostAlarm.description
                        wrapMode: Label.Wrap
                        font.pointSize: 14
                    }
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }

    }
}
