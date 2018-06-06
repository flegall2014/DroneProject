import QtQuick 2.5
import Components 1.0
import "../.."

ListView {
    id: dronePage
    interactive: false
    cacheBuffer: width > 0 ? 3*width : 0
    model: MASTERCONTROLLER.droneModel
    spacing: 3
    orientation: Qt.Horizontal
    clip: true
    opacity: 0
    visible: opacity > 0

    // Drone display
    delegate: DroneDisplay {
        id: droneDisplay
        width: dronePage.width/MASTERCONTROLLER.droneModel.droneCount
        height: dronePage.height
        clip: true
        targetDrone: drone
    }

    states: State {
        name: "visible"
        PropertyChanges {
            target: dronePage
            opacity: 1
        }
    }
    transitions: Transition {
        // Make the state changes smooth
        NumberAnimation {
            duration: Theme.standardAnimationDuration
            properties: "opacity"
        }
    }
}
