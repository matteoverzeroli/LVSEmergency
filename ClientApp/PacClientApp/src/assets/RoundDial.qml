import QtQuick 2.15
import QtQuick.Window 2.2
import CustomControls 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: rect
    Layout.alignment: Layout.Center
    width: 150
    height: 150
    color: "#D9D9D9"

    property alias tagName: name.text
    property alias minVal: radial.minValue
    property alias maxVale: radial.maxValue
    property alias value: radial.value
    property alias suffix: radial.suffixText


    Text {
        id: name
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        font.pointSize: 13
        color: "#F29F05"
        horizontalAlignment: Text.AlignHCenter
    }

    RadialBar {
        id: radial
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: parent.width / 1.4
        height: width
        penStyle: Qt.RoundCap
        progressColor: "#F29F05"
        foregroundColor: "#999999"
        dialWidth: 12
        textFont {
            family: "Halvetica"
            italic: false
            pointSize: 12
        }
        textColor: "#F29F05"

    }
}
