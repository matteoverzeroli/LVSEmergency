import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12


Item {

    Rectangle {
        anchors.fill: parent
        color: "transparent"


        AnimatedImage { id: animation;
            source: "qrc:/assets/LVSEmergencyBIGeffects.gif";
            anchors.centerIn: parent
            width: Math.min(parent.width, parent.height);
            height: Math.min(parent.width, parent.height)
        }
    }
}
