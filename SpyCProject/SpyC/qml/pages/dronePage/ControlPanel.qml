import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: root
    color: Theme.backgroundColor
    width: Theme.controlPanelWidth
    property variant targetDrone
    signal takeSnapShot()
    signal loadPanel(string panelName)

    ControlPanelWizard {
        anchors.fill: parent
        targetDrone: root.targetDrone
    }
}
