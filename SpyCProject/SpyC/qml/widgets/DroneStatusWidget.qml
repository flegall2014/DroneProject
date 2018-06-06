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

    /*
    // Battery status widget
    BatteryStatusWidget {
        id: batteryStatusWidget
        anchors.left: parent.left
        anchors.leftMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        batteryLevel: droneValid() ? targetDrone.batteryLevel : 0
        returnLevel: droneValid() ? targetDrone.returnLevel : 0
    }
    */

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height
        GridView {
            id: gridView
            anchors.fill: parent
            model: 10
            cellWidth: parent.width/5
            cellHeight: parent.height/2
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 3
                    color: "transparent"
                    border.color: "white"
                    StandardText {
                        horizontalAlignment: Text.AlignHCenter
                        anchors.centerIn: parent
                        text: "STATUS%" + index
                    }
                }
            }
        }
    }
}
