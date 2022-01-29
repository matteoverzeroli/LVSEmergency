import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    width: 400
    height: 640
    visible: true
    title: qsTr("PacApp")

    Component.onCompleted: contentFrame.replace("qrc:/views/LoginForm.qml");

    Connections {
        target: masterController.ui_navigationController

        function onGoDashboardView() {
            contentFrame.replace("qrc:/views/dashboard.qml")
        }

        function onGoLoginForm() {
            contentFrame.replace("qrc:/views/LoginForm.qml")
        }
    }


    StackView {
        id: contentFrame
        anchors.fill: parent
        initialItem: "qrc:/views/SplashView.qml"
        clip: true
    }
}
