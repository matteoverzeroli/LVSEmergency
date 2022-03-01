import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../assets"

Flickable {
    id: flickable

    contentHeight: column.height + 20

    Connections {
        target: masterController.ui_userController

        function onUserAddedWithSuccess() {
            busyIndicator.running = false
            userAddedDialog.open()

            masterController.ui_teamController.getTeams()
            volunteerRadio.checked = true
        }

        function onErrorOnAddingNewUser(error) {
            busyIndicator.running = false
            labelError.text = error
            userErrorDialog.open()
        }
    }

    Dialog {
        id: userAddedDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: Overlay.overlay

        modal: true
        title: "Utente inserito!"
        standardButtons: Dialog.Ok

        Column {
            spacing: 20
            anchors.fill: parent
            Label {
                width: parent.width
                text: "L'utente è stato inserito con successo!"
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
                id: labelError
                width: parent.width
                text: "Lo Username inserito è già in uso!"
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
            height: 48
            color: "transparent"

            Row {
                anchors.fill: parent
                Label {
                    id: userName
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Username:")

                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: userNameField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Username")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[a-zA-Z0-9\. ]{1,50}$/}
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"

            Row {
                anchors.fill: parent
                Label {
                    id: name
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Nome:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: nameField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Nome")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[a-zA-Z0-9 ]{1,50}$/}
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"

            Row {
                anchors.fill: parent
                Label {
                    id: surname
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Cognome:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: surnameField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Cognome")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[a-zA-Z0-9 ]{1,50}$/}
                }
            }
        }


        Rectangle {
            width: parent.width
            height: 80
            color: "transparent"

            Column {
                anchors.fill: parent
                Row {
                    width: parent.width
                    height: parent.height / 2
                    Label {
                        id: password
                        height: parent.height
                        width: parent.width / 2
                        text: qsTr("Password:")
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                    }

                    TextField {
                        id: passwordField
                        height: parent.height
                        width: parent.width / 2
                        placeholderText: qsTr("Inserisci Password")
                        echoMode: checkShowPassword.checked ? TextField.Normal : TextField.Password
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter

                    }
                }

                Row {
                    width: parent.width
                    height: parent.height / 2
                    Rectangle {
                        width: parent.width / 2
                        height: parent.height
                        color: "transparent"
                    }

                    CheckBox {
                        id: checkShowPassword
                        text: qsTr("Mostra password")
                        width: parent.width / 2
                        checked: false
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


        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"

            Row {
                anchors.fill: parent
                Label {
                    id: cf
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Codice Fiscale:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: cfField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Codice Fiscale")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[A-Z0-9]{16}$/}
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"
            Row {
                anchors.fill: parent
                Label {
                    id: sex
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Sesso:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                ComboBox {
                    id: comboSex
                    width: parent.width / 2
                    model: ["Maschio", "Femmina", "Preferisco non specificarlo"]
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"
            Row {
                anchors.fill: parent
                Label {
                    id: address
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Indirizzo:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: addressField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Indirizzo")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[a-zA-Z0-9 \.]{1,50}$/}
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"
            Row {
                anchors.fill: parent
                Label {
                    id: cellNumber
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Cellulare:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: cellNumberField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Cellulare")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /^[0-9]{10}$/}
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 48
            color: "transparent"
            Row {
                anchors.fill: parent
                Label {
                    id: email
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Email:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                TextField {
                    id: emailField
                    height: parent.height
                    width: parent.width / 2
                    placeholderText: qsTr("Email")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    validator: RegExpValidator{ regExp: /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/}
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

        ColumnLayout {
            id: columnRole
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                id: role
                height: 24
                text: qsTr("Ruolo:")
            }

            ButtonGroup {
                buttons: columnRole.children
            }

            RadioButton {
                id: volunteerRadio
                text: qsTr("Volontario")
                checked: true
                onCheckedChanged: {
                    if (checked)
                        comboTeam.model = masterController.ui_teamController.teamsAvailableList
                }
            }

            RadioButton {
                id: foremanRadio
                text: qsTr("Caposquadra")
                onCheckedChanged: {
                    if (checked)
                        comboTeam.model = masterController.ui_teamController.teamsAvailableWithoutForeman
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
                    id: team
                    height: parent.height
                    width: parent.width / 2
                    text: qsTr("Team:")
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                ComboBox {
                    id: comboTeam
                    height: parent.height
                    width: parent.width / 2
                    model: masterController.ui_teamController.teamsAvailableList
                }
            }
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: qsTr("Inserisci Utente")
                Layout.alignment: Layout.horizontalCenter

                highlighted: true

                onClicked: {
                    if (verifyFields()) {
                        var idTeam = masterController.ui_teamController.getIdTeamByName(comboTeam.currentText)

                        var role = 0;
                        if (volunteerRadio.checked)
                            role = 2
                        else
                            role = 1

                        var sex = 'X'
                        if (comboSex.currentIndex == 0) sex = 'M'
                        if (comboSex.currentIndex == 1) sex = 'F'

                        masterController.ui_userController.addUser(userNameField.text,
                                                                   nameField.text,
                                                                   surnameField.text,
                                                                   passwordField.text,
                                                                   cfField.text,
                                                                   addressField.text,
                                                                   cellNumberField.text,
                                                                   emailField.text,
                                                                   role, idTeam, sex)
                        busyIndicator.running = true
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
                            width: parent.width
                            text: "Verificare di aver inserito correttamente tutti i campi e riprovare."
                            wrapMode: Label.Wrap
                        }
                    }
                }

                function verifyFields () {
                    if (userNameField.acceptableInput && userNameField.text != ""
                            && nameField.acceptableInput && nameField.text != ""
                            && surnameField.acceptableInput && surnameField.text != ""
                            && passwordField.acceptableInput && passwordField.text != ""
                            && cfField.acceptableInput && cfField.text != ""
                            && addressField.acceptableInput && addressField.text != ""
                            && cellNumberField.acceptableInput && cellNumberField.text != ""
                            && emailField.acceptableInput && emailField.text != ""
                            && comboTeam.currentText != "")
                        return true

                    return false
                }
            }

            BusyIndicator {
                id: busyIndicator
                running: false
                width: opacity === 0 ? 0 : height
            }
        }

    }


    ScrollBar.vertical: ScrollBar { }
}
