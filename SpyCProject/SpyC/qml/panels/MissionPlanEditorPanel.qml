import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Qt.labs.platform 1.0
import ".."
import "../widgets"

PanelBase {
    centralTitle: qsTr("EDITING MISSION PLAN")
    property string requestor: ""
    onFileAccepted: {
        if (requestor === "load")
            MASTERCONTROLLER.loadMissionPlan(filePath)
        else
        if (requestor === "save")
            MASTERCONTROLLER.saveMissionPlan(filePath, targetDrone.uid)
    }

    leftToolBarContents: Item {
        anchors.fill: parent

        // Load
        ImageButton {
            id: load
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-open.svg"
            label: qsTr("Safety")
            textPosition: "below"
            enabled: droneValid()
            onClicked: {
                requestor = "load"
                openDialog(["*.mp"], FileDialog.OpenFile)
            }
        }

        // Save
        ImageButton {
            id: save
            anchors.left: load.right
            anchors.leftMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-save.svg"
            enabled: droneValid() && targetDrone.hasMissionPlan
            onClicked: {
                requestor = "save"
                openDialog(["*.mp"], FileDialog.SaveFile)
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
            model: droneValid() ? targetDrone.missionPlanModel : undefined
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
