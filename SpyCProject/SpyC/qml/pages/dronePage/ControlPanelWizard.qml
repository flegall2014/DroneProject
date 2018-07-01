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
            width: listView.width
            height: listView.height
        }

        // Exclusion page
        ExclusionPage {
            id: exclusionPage
            objectName: qsTr("EXCLUSION AREA")
            targetDrone: root.targetDrone
            width: listView.width
            height: listView.height
            clip: true
        }

        // Control page
        ControlPage {
            id: controlPage
            objectName: qsTr("ACTIONS")
            targetDrone: root.targetDrone
            width: listView.width
            height: listView.height
        }

        // Settings
        SettingsPage {
            id: settingsPage
            objectName: qsTr("SETTINGS")
            targetDrone: root.targetDrone
            width: listView.width
            height: listView.height
        }
    }

    Item {
        id: controlPanel
        width: parent.width
        height: parent.height*2/3
        anchors.top: parent.top
        Rectangle {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin
            border.color: Theme.defaultFontColor
            color: "transparent"

            Item {
                id: titleArea
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
                    color: "orange"
                }
            }

            // Page view
            ListView {
                id: listView
                anchors.top: titleArea.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                model: itemModel
                orientation: Qt.Horizontal
                snapMode: ListView.SnapOneItem
                clip: true
                onCurrentIndexChanged: currentPage.text = itemModel.get(currentIndex).objectName
                highlightRangeMode: ListView.StrictlyEnforceRange
            }

            // Next page
            ImageButton {
                anchors.right: parent.right
                anchors.rightMargin: Theme.standardMargin
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.standardMargin
                source: "qrc:/icons/ico-next.svg"
                enabled: listView.currentIndex < (itemModel.count-1)
                onClicked: {
                    var currentIndex = listView.currentIndex
                    currentIndex++
                    listView.currentIndex = currentIndex
                }
            }

            // Previous page
            ImageButton {
                anchors.left: parent.left
                anchors.leftMargin: Theme.standardMargin
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.standardMargin
                source: "qrc:/icons/ico-previous.svg"
                enabled: listView.currentIndex > 0
                onClicked: {
                    var currentIndex = listView.currentIndex
                    currentIndex--
                    listView.currentIndex = currentIndex
                }
            }
        }
    }

    // Alerts
    Item {
        id: alertPanel
        width: parent.width
        height: parent.height/3
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
