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

        ListView {
            width: parent.width/2
            height: parent.height
            model: droneValid() ? targetDrone.exclusionAreaModel : null
            spacing: 8
            clip: true

            delegate: Rectangle {
                color: "red"
                width: parent.width
                height: 32
                StandardText {
                    anchors.centerIn: parent
                    text: shape.strType
                }
            }
        }

        // Shape editor
        ShapeEditor {
            width: parent.width/2
            height: parent.height
            currentShape: droneValid() ? targetDrone.currentExclusionArea : null
        }
    }
}
