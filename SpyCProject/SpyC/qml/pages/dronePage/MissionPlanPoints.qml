import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import "../.."
import Components 1.0

// Draw mission plan way points
MapItemView {
    id: missionPlanWayPoints
    property variant targetDrone
    model: targetDrone.missionPlanModel
    property bool missionPlanVisible: true
    property color highlightColor: "white"
    delegate: Component {
        MapCircle {
            id: circle
            property bool selected: false
            center {
                latitude: wayPointLatitude
                longitude: wayPointLongitude
            }
            radius: 250
            color: missionPlanVisible ? highlightColor : "black"
            border.width: 3
            MouseArea {
                id: circleMouseArea
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                anchors.fill: parent
                enabled: targetDrone.workMode === SpyC.MISSION_PLAN_EDIT
                onClicked: {
                    if (mouse.button === Qt.RightButton)
                    {
                        targetDrone.removeCoordinateFromMissionPlanAtIndex(index)
                    }
                }
                onPressed: {
                    targetDrone.missionPlanModel.currentPointIndex = index
                    circle.selected = true
                }
                onPositionChanged: {
                    if (circle.selected)
                    {
                        var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                        targetDrone.setMissionPlanPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                    }
                }
                onReleased: {
                    circle.selected = false
                }
            }
        }
    }
}

