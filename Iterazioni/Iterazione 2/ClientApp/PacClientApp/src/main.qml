import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("PacApp")

//    Material.theme: Material.Light
//    Material.accent: Material.Green

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
