import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.platform 1.0
import ".."
import "../widgets"
import "../toolbars"

PanelBase {
    panelTitle: qsTr("EDITING SAFETY AREA")
    property string requestor: ""
    onFileAccepted: {
        if (requestor === "load")
            MASTERCONTROLLER.loadSafetyPlan(filePath)
        else
        if (requestor === "save")
            MASTERCONTROLLER.saveSafetyPlan(filePath, targetDrone.uid)
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
                openDialog(["*.sa"], FileDialog.OpenFile)
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
                openDialog(["*.sa"], FileDialog.SaveFile)
            }
        }
    }
    panelContents: Item {
        anchors.fill: parent

        WayPointView {
            anchors.fill: parent
            model: droneValid() ? targetDrone.safetyModel : undefined
        }
    }
}
