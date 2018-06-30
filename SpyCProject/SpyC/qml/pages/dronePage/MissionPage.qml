import QtQuick 2.5
import Components 1.0
import "../../widgets"
import "../.."

Grid {
    id: root
    columns: 3
    property variant targetDrone

    // Return true if drone is valid
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    // Safety
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-safety.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.SAFETY_EDIT
            onClicked: targetDrone.workMode = SpyC.SAFETY_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Safety")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }

    // Mission plan
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-missionplan.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.MISSION_PLAN_EDIT
            onClicked: targetDrone.workMode = SpyC.MISSION_PLAN_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Mission plan")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }

    // Landing
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-landingplan.svg"
            checkable: true
            checked: targetDrone.workMode === SpyC.LANDING_PLAN_EDIT
            onClicked: targetDrone.workMode = SpyC.LANDING_PLAN_EDIT
            enabled: targetDrone.flightStatus !== SpyC.FLYING
            label: qsTr("Landing plan")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }
}
