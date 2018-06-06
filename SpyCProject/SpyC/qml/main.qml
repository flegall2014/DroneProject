import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtLocation 5.3
import QtPositioning 5.6
import Components 1.0
import "."
import "pages/dronePage"
import "pages/loginPage"

// Main application window
ApplicationWindow {
    id: appWindow
    width: 512
    height: 512

    // App title
    property string appTitle: "Template"

    // Set visible
    visible: true

    // Visibility
    visibility: Window.Maximized

    Rectangle {
        anchors.fill: parent
        color: Theme.backgroundColor

        // Status bar
        ToolBar {
            id: toolBar
            width: parent.width
            height: Theme.toolBarHeight
            anchors.top: parent.top
            enabled: dialogMgr.state === ""
            showDroneStatus: MASTERCONTROLLER.currentDrone !== null
            mainTitle: MASTERCONTROLLER.currentDrone !== null ? "[" + MASTERCONTROLLER.currentDrone.uid + "]" + MASTERCONTROLLER.settingController.fullMissionName : qsTr("Welcome to Spy'C ground station") + TRANSLATOR.emptyString
        }

        // Login page
        LoginPage {
            id: loginPage
            anchors.bottom: statusBar.top
            anchors.top: toolBar.bottom
            width: parent.width
            onLoginClicked: {
                MASTERCONTROLLER.startComStation()
                loginPage.state = "hidden"
                dronePage.state = "visible"
            }
        }

        // Drone page
        DronePage {
            id: dronePage
            anchors.bottom: statusBar.top
            anchors.top: toolBar.bottom
            width: parent.width
            enabled: dialogMgr.state === ""
        }

        // Status bar
        StatusBar {
            id: statusBar
            width: parent.width
            height: Theme.toolBarHeight
            anchors.bottom: parent.bottom
            enabled: dialogMgr.state === ""
            onWindowsButtonClicked: {
                MASTERCONTROLLER.currentDrone.setDefaultWorkMode()
                MASTERCONTROLLER.currentDrone = null
            }
            windowsButtonVisible: MASTERCONTROLLER.currentDrone !== null
        }

        // Dialog manager
        DialogMgr {
            id: dialogMgr
            objectName: "dialogMgr"
            anchors.fill: parent

            // Safety error
            function onMissionPlanError(error, droneUID)
            {
                if (error === SpyC.EMPTY_SAFETY)
                    dialogMgr.showDialog(SpyC.EMPTY_SAFETY_ERROR, droneUID)
                else
                if (error === SpyC.NOT_ENOUGH_POINTS_IN_SAFETY)
                    dialogMgr.showDialog(SpyC.NOT_ENOUGH_POINT_IN_SAFETY, droneUID)
                else
                if (error === SpyC.EMPTY_MISSION_PLAN)
                    dialogMgr.showDialog(SpyC.EMPTY_MISSION_PLAN_ERROR, droneUID)
                else
                if (error === SpyC.NOT_ENOUGH_POINTS_IN_MISSION_PLAN)
                    dialogMgr.showDialog(SpyC.NOT_ENOUGH_POINT_IN_MISSION_PLAN, droneUID)
                else
                if (error === SpyC.EMPTY_LANDING_PLAN)
                    dialogMgr.showDialog(SpyC.EMPTY_LANDING_PLAN_ERROR, droneUID)
                else
                if (error === SpyC.UNEXPECTED_LANDING_PLAN_COUNT)
                    dialogMgr.showDialog(SpyC.UNEXPECTED_LANDING_PLAN_COUNT_ERROR, droneUID)
                return ""
            }

            Component.onCompleted: {
                MASTERCONTROLLER.missionPlanError.connect(onMissionPlanError)
            }
        }

        Component.onCompleted: MASTERCONTROLLER.settingController.say(MASTERCONTROLLER.applicationTitle)
    }
}
