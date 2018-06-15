import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../.."

// Exclusion area
MapItemView {
    id: root
    delegate: Component {
        MapCircle {
            id: circleShape
            color: Theme.exclusionAreaColor
            border.color: Theme.exclusionAreaBorderColor
            border.width: 3
            opacity: Theme.exclusionAreaOpacity
            visible: false
            property variant targetShape: shape

            Timer {
                interval: Theme.shapeBlinkInterval
                repeat: true
                running: ((shape === targetDrone.currentShape) && (targetDrone.workMode === SpyC.EXCLUSION_EDIT))
                onTriggered: {
                    if (border.color === Theme.exclusionAreaBorderColor)
                        border.color = Theme.exclusionAreaColor
                    else
                        border.color = Theme.exclusionAreaBorderColor
                }
                onRunningChanged: {
                    if (running === false)
                        border.color = Theme.exclusionAreaBorderColor
                }
            }

            center {
                latitude: shape.center.latitude
                longitude: shape.center.longitude
            }
            function onCurrentPathChanged()
            {
                if ((typeof targetShape !== "undefined") && (targetShape !== null))
                    circleShape.radius = targetShape.radius
            }
            onTargetShapeChanged: {
                if ((typeof targetShape !== "undefined") && (targetShape !== null))
                {
                    circleShape.visible = (targetShape.type === SpyC.CIRCLE)
                    if (circleShape.visible)
                    {
                        targetShape.pathChanged.connect(onCurrentPathChanged)
                        onCurrentPathChanged()
                    }
                }
            }
            MouseArea {
                id: mouseArea
                enabled: targetDrone.workMode === SpyC.EXCLUSION_EDIT
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                anchors.fill: parent
                onClicked: {
                    if (mouse.button === Qt.RightButton)
                        targetDrone.removeShape(index)
                }
                onPressed: {
                    targetDrone.currentShape = shape
                    mapView.gesture.enabled = false
                }
                onReleased: {
                    mapView.gesture.enabled = true
                }
                onPositionChanged: {
                    if (shape === targetDrone.currentShape)
                    {
                        var mapped = mouseArea.mapToItem(mapView, mouse.x, mouse.y)
                        var newPosition = mapView.toCoordinate(Qt.point(mapped.x, mapped.y))
                        shape.moveTo(newPosition)
                    }
                }
                onWheel: {
                    if (wheel.modifiers & Qt.ControlModifier) {
                        shape.rescale(wheel.angleDelta.y > 0 ? 1 : -1)
                    }
                    else
                    if (wheel.modifiers & Qt.ShiftModifier) {
                        shape.rotate(wheel.angleDelta.y > 0 ? 1 : -1)
                    }
                }
            }
        }
    }
}
