import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.15
import "../assets"

Page {
    id: flickable

    Connections {
        target: masterController.ui_userController

        function onUserDeletedWithSuccess() {
            userDeletedDialog.open()
        }

        function errorWhileDeletingUser() {
            userErrorDialog.open()
        }
    }

    Dialog {
        id: userDeletedDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: Overlay.overlay

        modal: true
        title: "Utente cancellato!"
        standardButtons: Dialog.Ok

        width: parent.width - 100

        Column {
            spacing: 20
            anchors.fill: parent
            Label {
                text: "L'utente è stato cancellato con successo!"
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

        modal: true
        title: "Attenzione!"
        standardButtons: Dialog.Ok
        width: parent.width - 100

        Column {
            spacing: 20
            anchors.fill: parent
            Label {
                text: "Errore durante la cancellazione dell'utente!"
                width: parent.width
                wrapMode: Label.Wrap
            }
        }
    }

    Label {
        id: info
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 8
        }

        height: 40
        width: parent.width
        wrapMode: Label.Wrap
        horizontalAlignment: Qt.AlignHCenter
        text: "Fai swipe verso sinistra per eliminare un utente."

    }

    ListView {
        id: allUsers
        width: parent.width
        anchors {
            top: info.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 20
        }

        model: masterController.ui_userController.users

        delegate: SwipeDelegate {
            id: swipeDelegate
            text: model.name + " " + model.surname
            width: parent.width
            height: model.role === 0 ? 0 : 40
            visible: model.role !== 0

            contentItem: Text {
                text: swipeDelegate.text
                font: swipeDelegate.font
                color: swipeDelegate.enabled ? (swipeDelegate.down ? "#F29F05" : "black") : "black"
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                Behavior on x {
                    enabled: !swipeDelegate.down
                    NumberAnimation {
                        easing.type: Easing.InOutCubic
                        duration: 400
                    }
                }
            }

            swipe.right: Label {
                id: deleteLabel
                text: qsTr("Cancella Utente")
                color: "white"
                verticalAlignment: Label.AlignVCenter
                padding: 12
                height: parent.height
                anchors.right: parent.right

                SwipeDelegate.onClicked: {
                    masterController.ui_userController.deleteUser(model.idUser)
                }

                background: Rectangle {
                    color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}
