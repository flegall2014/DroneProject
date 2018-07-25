import QtQuick 2.5
import Components 1.0
import ".."

// Top container
Grid {
    id: root
    property variant targetDrone
    spacing: Theme.standardSpacing
    columns: 5

    // Drone valid?
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    BatteryWidget {
        id: batLevel
        currentLevel: droneValid() ? targetDrone.batteryLevel : 0
        batteryColor: "green"
    }
    BatteryWidget {
        id: returnLevel
        currentLevel: droneValid() ? targetDrone.returnLevel : 0
        batteryColor: "orange"
    }
}
