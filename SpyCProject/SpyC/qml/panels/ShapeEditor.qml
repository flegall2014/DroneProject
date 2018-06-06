import QtQuick 2.5
import "../widgets"
import Components 1.0
import ".."

Item {
    property variant currentShape

    Component {
        id: circleEditorComponent
        Item {
            anchors.fill: parent
            Column {
                width: parent.width/2
                height: 2*Theme.standardDelegateHeight
                anchors.centerIn: parent
                CoordinateEditor {
                    id: delegate
                    coordinate: currentShape.center
                }
                StandardLabelTextField {
                    label: qsTr("Radius")
                    text: currentShape.radius
                }
            }
        }
    }
    Component {
        id: polygonEditorComponent
        Item {
            anchors.fill: parent
            ListView {
                width: parent.width/2
                height: Theme.standardDelegateHeight*currentShape.count
                anchors.centerIn: parent
                interactive: false
                model: currentShape.count
                delegate: CoordinateEditor {
                    id: delegate
                    coordinate: currentShape.path.coordinateAt(index)
                    onLatitudeChanged: {
                        currentShape.setLatitudeAtIndex(index, latitude)
                    }
                    onLongitudeChanged: {
                        currentShape.setLongitudeAtIndex(index, longitude)
                    }
                    onAltitudeChanged: {
                        currentShape.setAltitudeAtIndex(index, altitude)
                    }
                }
            }
        }
    }

    Loader {
        id: shapeEditorLoader
        anchors.fill: parent
    }

    onCurrentShapeChanged: {
        if ((typeof currentShape !== "undefined") && (currentShape !== null))
        {
            if (currentShape.type === BaseShape.CIRCLE)
                shapeEditorLoader.sourceComponent = circleEditorComponent
            else
                shapeEditorLoader.sourceComponent = polygonEditorComponent
        }
        else shapeEditorLoader.sourceComponent = null
    }
}
