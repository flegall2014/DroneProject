import QtQuick 2.5
import ".."
import "../widgets"

PanelBase {
    id: root
    panelTitle: qsTr("Flight Editor")
    blinking: false
    panelContents: Item {
        anchors.fill: parent

        AltitudeWidget {
            size: 256
            anchors.centerIn: parent
            heading: root.droneValid() ? root.targetDrone.heading : 0
        }
    }
}
