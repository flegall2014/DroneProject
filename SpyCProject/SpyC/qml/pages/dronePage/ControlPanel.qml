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

    TabView {
        anchors.fill: parent
        // Commands tab
        Tab {
            title: qsTr("Commands")
            Item {
                anchors.fill: parent
                anchors.margins: Theme.standardMargin
                DroneActions {
                    anchors.fill: parent
                    targetDrone: root.targetDrone
                    onTakeSnapShot: root.takeSnapShot()
                }
            }
        }

        // Alerts tab
        Tab {
            title: qsTr("Alerts")
            Item {
                anchors.fill: parent
                anchors.margins: Theme.standardMargin
                DroneAlertView {
                    anchors.fill: parent
                    targetDrone: root.targetDrone
                }
            }
        }

        style: Theme.controlPanelTabViewStyle
    }
}
