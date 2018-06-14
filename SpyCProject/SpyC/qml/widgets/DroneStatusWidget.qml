import QtQuick 2.5
import Components 1.0
import ".."

// Top container
Item {
    id: root
    property variant targetDrone

    // Drone valid?
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height
        GridView {
            id: gridView
            anchors.fill: parent
            model: 6
            cellWidth: parent.width/3
            cellHeight: parent.height/2
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight
                BatteryWidget {
                    id: batLevel
                    anchors.centerIn: parent
                    currentLevel: droneValid() ? targetDrone.batteryLevel : 0
                    batteryColor: "green"
                    visible: index%2 !== 0
                }
                BatteryWidget {
                    id: returnLevel
                    anchors.centerIn: parent
                    currentLevel: droneValid() ? targetDrone.returnLevel : 0
                    batteryColor: "orange"
                    visible: index%2 === 0
                }
            }
        }
    }
}
