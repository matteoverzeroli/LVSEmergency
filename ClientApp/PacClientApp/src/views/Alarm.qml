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

        contentHeight: pane.height

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

        Pane {
            id: pane
            width: flickable.width

            Column {
                id: column
                width: parent.width - 40
                x: 20
                spacing: 16

                function getText(type) {
                    if (type === "FOG")
                        return "Nebbia"
                    if (type === "FROST")
                        return "Brina"
                    if (type === "BW")
                        return "Maltempo"
                }

                function getColor(color) {
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

                function getForeground(color){
                    if (color === "NONE" || color === "WHITE")
                        return "#000000"

                    return "#FFFFFF"
                }

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

                    Material.background: column.getColor(masterController.ui_areaController.frogorfrostAlarm.color)
                    Material.foreground: column.getForeground(masterController.ui_areaController.frogorfrostAlarm.color)



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
                            text: column.getText(masterController.ui_areaController.frogorfrostAlarm.type)
                            width: parent.width

                            horizontalAlignment: Qt.AlignHCenter
                            font.bold: true
                            font.pointSize: 16
                        }


                        Label {
                            text: masterController.ui_areaController.frogorfrostAlarm.description
                            wrapMode: Label.Wrap
                            font.pointSize: 12
                            width: parent.width
                        }
                    }
                }

                RoundPane {
                    Material.elevation: 6
                    radius: 6
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: parent.width * 4 / 5

                    Material.background: column.getColor(masterController.ui_areaController.badwheatherAlarm.color)
                    Material.foreground: column.getForeground(masterController.ui_areaController.badwheatherAlarm.color)



                    Column {
                        spacing: 8
                        width: parent.width

                        Label {
                            id: alarmDateBw
                            text: masterController.ui_areaController.badwheatherAlarm.date
                            width: parent.width

                            horizontalAlignment: Qt.AlignLeft
                            font.pointSize: 10
                        }

                        Label {
                            id: alarmTypeBw
                            text: column.getText(masterController.ui_areaController.badwheatherAlarm.type)
                            width: parent.width

                            horizontalAlignment: Qt.AlignHCenter
                            font.bold: true
                            font.pointSize: 16
                        }


                        Label {
                            text: masterController.ui_areaController.badwheatherAlarm.description
                            wrapMode: Label.Wrap
                            font.pointSize: 12
                            width: parent.width
                        }
                    }
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }

    }
}
