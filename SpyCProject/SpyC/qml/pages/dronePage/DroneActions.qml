import QtQuick 2.0
import Components 1.0
import "../../widgets"
import "../.."

Grid {
    id: droneActions
    columns: 3
    property variant targetDrone
    signal takeSnapShot()

    //
    // Planning
    //

    // Safety
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-safety.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.SAFETY_EDIT
            onClicked: targetDrone.workMode = SpyC.SAFETY_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Safety")
            textPosition: "below"
        }
    }

    // Mission plan
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-missionplan.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.MISSION_PLAN_EDIT
            onClicked: targetDrone.workMode = SpyC.MISSION_PLAN_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Mission plan")
            textPosition: "below"
        }
    }

    // Landing
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-landingplan.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.LANDING_PLAN_EDIT
            onClicked: targetDrone.workMode = SpyC.LANDING_PLAN_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Landing plan")
            textPosition: "below"
        }
    }

    // Exclusion area
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-exclude.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.EXCLUSION_EDIT
            onClicked: targetDrone.workMode = SpyC.EXCLUSION_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Exclusion area")
            textPosition: "below"
        }
    }

    //
    // Actions
    //

    // Take off
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-takeoff.svg"
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_TAKE_OFF)
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Take off")
            textPosition: "below"
        }
    }

    // Fail safe
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-crash.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_FAILSAFE)
            label: qsTr("Fail safe")
            textPosition: "below"
        }
    }

    // Go home
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-home.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_GO_HOME)
            label: qsTr("Go home")
            textPosition: "below"
        }
    }

    // Go to
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-ground.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            label: qsTr("GoTo")
            textPosition: "below"
        }
    }

    // Ruler
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-ruler.svg"
            label: qsTr("Ruler")
            textPosition: "below"
        }
    }

    // Snapshot
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-snapshot.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            label: qsTr("Snapshot")
            textPosition: "below"
            onClicked: takeSnapShot()
        }
    }

    // Gallery
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            anchors.centerIn: parent
            source: "qrc:/icons/ico-gallery.svg"
            enabled: true
            label: qsTr("Gallery")
            textPosition: "below"
            onClicked: {
                targetDrone.galleryModel.initialize()
                targetDrone.workMode = SpyC.GALLERY_EDIT
            }
        }
    }
}
