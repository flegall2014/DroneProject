import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import ".."
import "../widgets"
import "../toolbars"

PanelBase {
    centralTitle: qsTr("EDITING SAFETY AREA")
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

        WayPointView {
            anchors.fill: parent
            model: droneValid() ? targetDrone.safetyModel : undefined
        }
    }
}
