import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: root
    color: Theme.backgroundColor
    width: Theme.controlPanelWidth
    property bool goNextEnabled: false
    property string armyText: ""
    property string unitText: ""
    property string missionText: ""
    property string operatorText: ""
    signal loginClicked()

    Item {
        id: tabViewContainer
        width: parent.width/2
        height: parent.height
        anchors.centerIn: parent

        // Main tab view
        TabView {
            id: tabView
            anchors.fill: parent

            // Login tab
            Tab {
                title: qsTr("Login") + TRANSLATOR.emptyString
                LoginTab {
                    id: loginTab
                    anchors.fill: parent
                    anchors.margins: Theme.standardMargin
                    onLoginClicked: root.loginClicked()
                    onGoNextEnabledChanged: root.goNextEnabled = loginTab.goNextEnabled
                    onArmyTextChanged: root.armyText = loginTab.armyText
                    onUnitTextChanged: root.unitText = loginTab.unitText
                    onMissionTextChanged: root.missionText = loginTab.missionText
                    onOperatorTextChanged: root.operatorText = loginTab.operatorText
                }
            }

            // Settings
            Tab {
                title: qsTr("Settings") + TRANSLATOR.emptyString
                SettingsTab {
                    id: settingsTab
                    anchors.fill: parent
                    anchors.margins: Theme.standardMargin
                }
            }

            style: Theme.loginPageTabViewStyle
        }

        // Hand
        HandWidget {
            anchors.right: langWidget.left
            anchors.rightMargin: 16
            anchors.top: parent.top
        }

        // Language
        LangWidget {
            id: langWidget
            anchors.right: parent.right
            anchors.top: parent.top
        }
    }

    // SpyRanger
    Item {
        id: leftArea
        anchors.left: parent.left
        anchors.right: tabViewContainer.left
        height: parent.height
        Image {
            id: spyRangerImg
            source: "qrc:/images/img-spyranger.png"
            anchors.centerIn: parent
            scale: .5
            StandardText {
                anchors.top: parent.bottom
                anchors.topMargin: Theme.standardMargin
                text: qsTr("Spy'Ranger by THALES") + TRANSLATOR.emptyString
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: Theme.largeFontSize
                font.bold: true
            }
            states: State {
                name: "maximized"
                PropertyChanges {
                    target: spyRangerImg
                    scale: 1
                    rotation: 360
                }
            }
            transitions: Transition {
                // Make the state changes smooth
                NumberAnimation {
                    duration: 2*Theme.standardAnimationDuration
                    properties: "scale, rotation"
                }
            }
        }
    }

    // Go next
    Item {
        id: rightArea
        anchors.left: tabViewContainer.right
        anchors.right: parent.right
        height: parent.height

        // Go next
        ImageButton {
            id: goNext
            anchors.centerIn: parent
            source: "qrc:/icons/ico-go-right.svg"
            enabled: root.goNextEnabled
            width: Theme.goNextIconSize
            height: Theme.goNextIconSize
            onClicked: loginClicked()
        }
    }

    states: State {
        name: "hidden"
        PropertyChanges {
            target: loginPage
            opacity: 0
        }
    }
    transitions: Transition {
        NumberAnimation {duration: Theme.standardAnimationDuration; properties: "opacity"}
    }

    Component.onCompleted: spyRangerImg.state = "maximized"
}
