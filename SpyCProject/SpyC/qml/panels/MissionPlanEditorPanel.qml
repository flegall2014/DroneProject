import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Qt.labs.platform 1.0
import ".."
import "../widgets"

PanelBase {
    centralTitle: qsTr("EDITING MISSION PLAN")
    leftToolBarContents: Item {
        anchors.fill: parent

        // Load
        ImageButton {
            id: load
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-open.svg"
        }

        // Save
        ImageButton {
            id: save
            anchors.left: load.right
            anchors.leftMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-save.svg"
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
