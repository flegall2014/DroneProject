import QtQuick 2.5
import QtQml.Models 2.1
import "../../"
import "../../widgets"

Item {
    id: root
    property variant targetDrone

    ObjectModel {
        id: itemModel

        // Mission page
        MissionPage {
            id: missionPage
            objectName: qsTr("MISSION PLAN")
            targetDrone: root.targetDrone
            width: root.width
            height: root.height
        }

        // Exclusion page
        ExclusionPage {
            id: exclusionPage
            objectName: qsTr("EXCLUSION AREA")
            targetDrone: root.targetDrone
            width: root.width
            height: root.height
        }

        // Control page
        ControlPage {
            id: controlPage
            objectName: qsTr("ACTIONS")
            targetDrone: root.targetDrone
            width: root.width
            height: root.height
        }

        // Settings
        SettingsPage {
            id: settingsPage
            objectName: qsTr("SETTINGS")
            targetDrone: root.targetDrone
            width: root.width
            height: root.height
        }
    }

    Item {
        id: controlPanel
        width: parent.width
        height: parent.height/2
        anchors.top: parent.top
        Rectangle {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin
            border.color: Theme.defaultFontColor
            color: "transparent"
            Item {
                id: titleArea1
                anchors.top: parent.top
                width: parent.width
                height: Theme.buttonSize/2
                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Theme.defaultFontColor
                }
                StandardText {
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Control Panel")
                }
                StandardText {
                    id: currentPage
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: itemModel.get(0).objectName
                }
            }

            ListView {
                anchors.top: titleArea1.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                model: itemModel
                orientation: Qt.Horizontal
                snapMode: ListView.SnapOneItem
                clip: true
                onCurrentIndexChanged: currentPage.text = itemModel.get(currentIndex).objectName
                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }
    }

    // Alerts
    Item {
        id: alertPanel
        width: parent.width
        height: parent.height/2
        anchors.top: controlPanel.bottom
        Rectangle {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin
            border.color: Theme.defaultFontColor
            color: "transparent"
            Item {
                id: titleArea2
                anchors.top: parent.top
                width: parent.width
                height: Theme.buttonSize/2
                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: Theme.defaultFontColor
                }
                StandardText {
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Alerts")
                }
            }

            DroneAlertView {
                anchors.top: titleArea2.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                targetDrone: root.targetDrone
            }
        }
    }
}