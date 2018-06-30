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

    // Navigation
    Item {
        width: parent.width/3
        height: width
        ImageButton {
            endColor: Theme.defaultButtonColor
            source: "qrc:/icons/ico-navigation.svg"
            enabled: targetDrone.flightStatus === SpyC.FLYING
            label: qsTr("Navigation")
            textPosition: "below"
            anchors.centerIn: parent
            textColor: Theme.defaultFontColor
            onClicked: loadPanel("FlightEditor")
        }
    }
}
