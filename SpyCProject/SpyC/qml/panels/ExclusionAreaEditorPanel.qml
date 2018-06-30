import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Qt.labs.platform 1.0
import Components 1.0
import ".."
import "../widgets"

PanelBase {
    id: root
    panelTitle: qsTr("EDITING EXCLUSION AREA")
    property string requestor: ""
    onFileAccepted: {
        if (requestor === "load")
            MASTERCONTROLLER.loadExclusionArea(filePath)
        else
        if (requestor === "save")
            MASTERCONTROLLER.saveExclusionArea(filePath, targetDrone.uid)
    }

    leftToolBarContents: Item {
        anchors.fill: parent

        // Load
        ImageButton {
            id: load
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-open.svg"
            onClicked: {
                requestor = "load"
                openDialog(["*.excl"], FileDialog.OpenFile)
            }
        }

        // Save
        ImageButton {
            id: save
            anchors.left: load.right
            anchors.leftMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-save.svg"
            onClicked: {
                requestor = "save"
                openDialog(["*.excl"], FileDialog.SaveFile)
            }
        }
    }
    panelContents: Row {
        anchors.fill: parent

        Item {
            width: parent.width/2
            height: parent.height

            Row {
                anchors.centerIn: parent
                spacing: Theme.buttonSize
                ImageButton {
                    id: circleExclusion
                    source: "qrc:/icons/ico-circle.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    label: qsTr("Circle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: targetDrone.currentExclusionShape = SpyC.CIRCLE
                    checkable: true
                    checked: root.droneValid() ? (targetDrone.currentExclusionShape === SpyC.CIRCLE) : false
                }
                ImageButton {
                    id: rectExclusion
                    source: "qrc:/icons/ico-rectangle.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    label: qsTr("Rectangle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: targetDrone.currentExclusionShape = SpyC.RECTANGLE
                    checkable: true
                    checked: root.droneValid() ? (targetDrone.currentExclusionShape === SpyC.RECTANGLE) : false
                }
                ImageButton {
                    id: triangleExclusion
                    source: "qrc:/icons/ico-triangle.svg"
                    anchors.verticalCenter: parent.verticalCenter
                    label: qsTr("Triangle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: targetDrone.currentExclusionShape = SpyC.TRIANGLE
                    checkable: true
                    checked: root.droneValid() ? (targetDrone.currentExclusionShape === SpyC.TRIANGLE) : false
                }
            }
        }

        // Shape editor
        ShapeEditor {
            width: parent.width/2
            height: parent.height
            currentShape: droneValid() ? targetDrone.currentShape : null
        }
    }
}
