import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Page {
    id: window

    Action {
        id: navigateBackAction
        icon.name: stackView.depth > 1 ? "back" : "drawer"
        onTriggered: {
            if (stackView.depth > 1) {
                stackView.pop()
//                listView.currentIndex = -1
            } else {
                drawer.open()
            }
        }
    }

    Action {
        id: optionsMenuAction
        icon.name: "menu"
        onTriggered: optionsMenu.open()
    }

    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                action: navigateBackAction
            }

            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : "Dashboard"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                action: optionsMenuAction

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    Action {
                        text: "Logout"
                        onTriggered: {
                            masterController.ui_navigationController.needLoginForm();
                        }
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        interactive: stackView.depth === 1

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: listView.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }

//            model: ListModel {
//                ListElement { title: "BusyIndicator"; source: "qrc:/pages/BusyIndicatorPage.qml" }
//                ListElement { title: "Button"; source: "qrc:/pages/ButtonPage.qml" }
//                ListElement { title: "CheckBox"; source: "qrc:/pages/CheckBoxPage.qml" }
//                ListElement { title: "ComboBox"; source: "qrc:/pages/ComboBoxPage.qml" }
//                ListElement { title: "DelayButton"; source: "qrc:/pages/DelayButtonPage.qml" }
//                ListElement { title: "Dial"; source: "qrc:/pages/DialPage.qml" }
//                ListElement { title: "Dialog"; source: "qrc:/pages/DialogPage.qml" }
//                ListElement { title: "Delegates"; source: "qrc:/pages/DelegatePage.qml" }
//                ListElement { title: "Frame"; source: "qrc:/pages/FramePage.qml" }
//                ListElement { title: "GroupBox"; source: "qrc:/pages/GroupBoxPage.qml" }
//                ListElement { title: "PageIndicator"; source: "qrc:/pages/PageIndicatorPage.qml" }
//                ListElement { title: "ProgressBar"; source: "qrc:/pages/ProgressBarPage.qml" }
//                ListElement { title: "RadioButton"; source: "qrc:/pages/RadioButtonPage.qml" }
//                ListElement { title: "RangeSlider"; source: "qrc:/pages/RangeSliderPage.qml" }
//                ListElement { title: "ScrollBar"; source: "qrc:/pages/ScrollBarPage.qml" }
//                ListElement { title: "ScrollIndicator"; source: "qrc:/pages/ScrollIndicatorPage.qml" }
//                ListElement { title: "Slider"; source: "qrc:/pages/SliderPage.qml" }
//                ListElement { title: "SpinBox"; source: "qrc:/pages/SpinBoxPage.qml" }
//                ListElement { title: "StackView"; source: "qrc:/pages/StackViewPage.qml" }
//                ListElement { title: "SwipeView"; source: "qrc:/pages/SwipeViewPage.qml" }
//                ListElement { title: "Switch"; source: "qrc:/pages/SwitchPage.qml" }
//                ListElement { title: "TabBar"; source: "qrc:/pages/TabBarPage.qml" }
//                ListElement { title: "TextArea"; source: "qrc:/pages/TextAreaPage.qml" }
//                ListElement { title: "TextField"; source: "qrc:/pages/TextFieldPage.qml" }
//                ListElement { title: "ToolTip"; source: "qrc:/pages/ToolTipPage.qml" }
//                ListElement { title: "Tumbler"; source: "qrc:/pages/TumblerPage.qml" }
//            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Pane {
            id: pane

            Label {
                text: "Qt Quick Controls 2 provides a set of controls that can be used to build complete interfaces in Qt Quick."
                anchors.margins: 20
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                wrapMode: Label.Wrap
            }
        }
    }



}
