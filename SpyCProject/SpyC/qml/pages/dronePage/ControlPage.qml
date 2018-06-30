import QtQuick 2.5
import Components 1.0
import "../../widgets"
import "../.."

Grid {
    id: root
    columns: 3
    property variant targetDrone

    // Take off
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            id: canTakeOffBtn
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-takeoff.svg"
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_TAKE_OFF)
            enabled: (targetDrone.flightStatus !== SpyC.FLYING) && (targetDrone.canTakeOff)
            label: qsTr("Take off")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }

    // Fail safe
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-crash.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_FAILSAFE)
            label: qsTr("Fail safe")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }

    // Go home
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-home.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            onClicked: dialogMgr.showDialog(SpyC.CONFIRM_GO_HOME)
            label: qsTr("Go home")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
        }
    }

    // Go to
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-ground.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            label: qsTr("GoTo")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
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
            textColor: Theme.defaultFontColor
            onClicked: takeSnapShot()
        }
    }
}
