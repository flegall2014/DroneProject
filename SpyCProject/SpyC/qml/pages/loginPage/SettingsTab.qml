import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0

    // Main container
    Rectangle {
        id: mainContainer
        width: parent.width
        height: parent.height-2*Theme.toolBarHeight
        anchors.centerIn: parent
        color: "transparent"
        radius: 8
        border.color: "white"

        Item {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin*2

            // Maps
            Item {
                id: mapGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: parent.top
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Maps") + TRANSLATOR.emptyString
                    folder: MASTERCONTROLLER.settingController.mapPath
                    selectedFolder: MASTERCONTROLLER.settingController.mapPath
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.mapPath = selectedFolder
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: mapGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Mission") + TRANSLATOR.emptyString
                    folder: MASTERCONTROLLER.settingController.missionPath
                    selectedFolder: MASTERCONTROLLER.settingController.missionPath
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.missionPath = selectedFolder
                }
            }

            // Logs
            Item {
                id: logGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Logs") + TRANSLATOR.emptyString
                    folder: MASTERCONTROLLER.settingController.logPath
                    selectedFolder: MASTERCONTROLLER.settingController.logPath
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.logPath = selectedFolder
                }
            }

            // Alerts
            Item {
                id: alertGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: logGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Alerts") + TRANSLATOR.emptyString
                    folder: MASTERCONTROLLER.settingController.alertPath
                    selectedFolder: MASTERCONTROLLER.settingController.alertPath
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.alertPath = selectedFolder
                }
            }

            // Gallery
            Item {
                id: galleryGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: alertGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Gallery") + TRANSLATOR.emptyString
                    folder: MASTERCONTROLLER.settingController.galleryPath
                    selectedFolder: MASTERCONTROLLER.settingController.galleryPath
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.galleryPath = selectedFolder
                }
            }
        }
    }
}
