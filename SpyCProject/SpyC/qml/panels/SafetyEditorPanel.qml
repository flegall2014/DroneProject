import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import ".."
import "../widgets"
import "../toolbars"

PanelBase {
    centralTitle: qsTr("EDITING SAFETY AREA")
    panelContents: Item {
        anchors.fill: parent

        WayPointView {
            anchors.fill: parent
            model: droneValid() ? targetDrone.safetyModel : undefined
        }
    }
}
