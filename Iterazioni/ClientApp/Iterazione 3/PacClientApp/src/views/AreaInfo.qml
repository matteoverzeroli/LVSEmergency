import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Item {

    Connections {
        target: masterController.ui_areaController

        function onAprsDataChanged() {
            if (masterController.ui_areaController.aprsData === null) {
                dataErrorDialog.open()
            } else {
                loading.running = false
                flickable.visible = true
            }
        }

        function onAprsDataError() {
            dataErrorDialog.open()
        }
    }

    BusyIndicator {
        id: loading
        running: true
        anchors.centerIn: parent
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

    Flickable {
        id: flickable
        anchors.fill: parent

        visible: false

        contentHeight: pane.height

        Pane {
            id: pane
            width: flickable.width

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
                    text: "Ecco i dati di " +
                          masterController.ui_teamController.currentTeam.area.areaName+":"

                    font.pointSize: 12
                }

                RoundPane {
                    Material.elevation: 6
                    radius: 6
                    anchors.horizontalCenter: parent.horizontalCenter

                    Column {

                        Label {
                            text: masterController.ui_areaController.aprsData === null ?
                                      "" : masterController.ui_areaController.aprsData.date
                            width: parent.width
                            color: "#F29F05"

                            horizontalAlignment: Qt.AlignHCenter
                            font.pointSize: 10
                        }

                        Rectangle {
                            height: 2
                            width: parent.width * 5 / 6
                            radius: 5
                            anchors.horizontalCenter: parent.horizontalCenter

                            color: "#999999"
                        }

                        GridLayout {
                            rows: 3; columns: 2
                            columnSpacing: 0; rowSpacing: 0

                            RoundDial {
                                tagName: qsTr("Temperatura")
                                minVal: -20
                                maxVale: 50
                                value: masterController.ui_areaController.aprsData.temperature
                                suffix: "°"
                            }

                            RoundDial {
                                tagName: qsTr("Umidità")
                                minVal: 0
                                maxVale: 100
                                value: masterController.ui_areaController.aprsData.humidity
                                suffix: "%"
                            }

                            RoundDial {
                                tagName: qsTr("Pressione")
                                minVal: 900
                                maxVale: 1100
                                value: masterController.ui_areaController.aprsData.pressure
                                suffix: "hPa"
                            }

                            RoundDial {
                                tagName: qsTr("Pioggia in un ora")
                                minVal: 0
                                maxVale: 5
                                value: masterController.ui_areaController.aprsData.rainOneHour
                                suffix: "mm"
                            }

                            RoundDial {
                                tagName: qsTr("Velocità Vento")
                                minVal: 0
                                maxVale: 40
                                value: masterController.ui_areaController.aprsData.windSpeed
                                suffix: "m/s"
                            }

                            RoundDial {
                                tagName: qsTr("Direzione Vento")
                                minVal: 0
                                maxVale: 359
                                value: masterController.ui_areaController.aprsData.windDirection
                                suffix: "°"
                            }                            
                        }
                    }
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }

    }
}
