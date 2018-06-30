import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Qt.labs.platform 1.0
import ".."
import "../widgets"

PanelBase {
    panelTitle: qsTr("EDITING LANDING PLAN")
    property string requestor: ""
    onFileAccepted: {
        if (requestor === "load")
            MASTERCONTROLLER.loadLandingPlan(filePath)
        else
        if (requestor === "save")
            MASTERCONTROLLER.saveLandingPlan(filePath, targetDrone.uid)
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
                openDialog(["*.la"], FileDialog.OpenFile)
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
                openDialog(["*.la"], FileDialog.SaveFile)
            }
        }
    }
    panelContents: Item {
        anchors.fill: parent

        // Way point view
        WayPointView {
            anchors.left: parent.left
            anchors.right: singlePointEditor.left
            height: parent.height
            model: droneValid() ? targetDrone.landingPlanModel : undefined
        }

        // Single point editor
        SinglePointEditor {
            id: singlePointEditor
            anchors.right: parent.right
            width: parent.height
            height: parent.height
        }
    }
}
