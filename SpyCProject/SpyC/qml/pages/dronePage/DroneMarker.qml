import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../../widgets"
import "../.."

// Drone marker
MapQuickItem {
    id: droneMarker
    anchorPoint.x: droneItem.width  / 2
    anchorPoint.y: droneItem.height / 2
    coordinate: targetDrone.position
    property variant targetDrone

    sourceItem: Item {
        id: droneItem
        width: droneIcon.width
        height: droneIcon.height
        property int size: 48

        Image {
            id: droneIcon
            source: "qrc:/icons/ico-drone2.svg"
            mipmap: true
            width: droneItem.size
            sourceSize.width: droneItem.size
            fillMode: Image.PreserveAspectFit
            transform: Rotation {
                origin.x: droneIcon.width /2
                origin.y: droneIcon.height/2
                angle: targetDrone.heading
            }
        }
    }
}
