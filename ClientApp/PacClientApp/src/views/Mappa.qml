import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.2
import "../assets"

Page {

    Connections {
        target: masterController.ui_userController

    }

    Timer {
        interval: 10000; running: true; repeat: true
        onTriggered: {
            masterController.ui_userController.getUsersPosition(
                        masterController.ui_teamController.currentTeam.usersId);

        }
    }

    Label {
        id: info
        width: parent.width
        anchors.top: parent.top
        anchors.margins: 10
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        text: "Ecco dove si trovano i tuoi compagni operativi:"
    }

    RoundPane {
        Material.elevation: 6
        radius: 6
        anchors {
            top: info.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        visible: masterController.ui_teamController.currentTeam === null ? false : true

        width: parent.width * 4 / 5
        height: parent.width * 4 / 5

        Plugin {
            id: mapPlugin
            name: "osm"
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            zoomLevel: 14

            property string selectedName: ""
            property string selectedSurname: ""
            property bool dragged: false


            RoundPane {
                id: pane
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    margins: 10
                }

                height: column.height + 20

                Material.foreground: "white"
                Material.background: "#F29F05"
                Material.elevation: 6
                radius: 6

                Behavior on opacity {
                    NumberAnimation {duration: 500}
                }

                opacity: 0

                Column {
                    id: column
                    spacing: 8
                    Row {
                        spacing: 8
                        Label {
                            text: qsTr("Nome:")
                            font.bold: true
                        }

                        Label {
                            text: map.selectedName
                            font.bold: true
                        }
                    }

                    Row {
                        spacing: 8
                        Label {
                            text: qsTr("Cognome:")
                            font.bold: true
                        }

                        Label {
                            text: map.selectedSurname
                            font.bold: true
                        }
                    }
                }

                Timer {
                    id: timerHide
                    interval: 5000; running: false; repeat: false
                    onTriggered: {
                        pane.opacity = 0
                        map.selectedName = ""
                        map.selectedSurname = ""
                    }
                }
            }

            MapItemView {
                model: masterController.ui_userController.colleguePositions
                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(
                                    model.latitude,
                                    model.longitude)

                    anchorPoint.x: imagePos.width * 0.5
                    anchorPoint.y: imagePos.height

                    sourceItem: Image {
                        id: imagePos
                        source: getImage()
                        height: 32
                        width: 25
                        fillMode: Image.PreserveAspectFit

                        function getImage() {
                            if (map.selectedName === model.name
                                    && map.selectedSurname === map.selectedSurname)
                                return "qrc:/assets/marker_red.png"

                            return "qrc:/assets/marker_blue.png"
                        }
                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                pane.opacity = 100
                                timerHide.interval = 5000
                                timerHide.running = true

                                map.selectedName = model.name
                                map.selectedSurname = model.surname
                            }
                        }
                    }

                    Component.onCompleted: {
                        if (map.dragged === false) {
                            map.center = QtPositioning.coordinate(
                                        model.latitude,
                                        model.longitude)
                            map.dragged = true
                        }
                    }
                }
            }
        }
    }
}

