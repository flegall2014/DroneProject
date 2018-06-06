import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import ".."
import "../widgets"

PanelBase {
    centralTitle: qsTr("EDITING MISSION PLAN")
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
