import QtQuick 2.5
import Components 1.0
import "."
import "./widgets"

// Status bar
Rectangle {
    id: statusBar
    color: Theme.statusBarColor
    property bool windowsButtonVisible: false
    signal windowsButtonClicked()

    // Windows button
    ImageButton {
        id: windowsButton
        visible: windowsButtonVisible
        anchors.left: parent.left
        anchors.leftMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-windows.svg"
        onClicked: windowsButtonClicked()
    }

    // Other drone display
    Item {
        id: otherDroneDisplay
        anchors.left: windowsButton.right
        anchors.leftMargin: Theme.standardMargin
        width: 512
        height: parent.height
        visible: MASTERCONTROLLER.currentDrone !== null
        ListView {
            id: listView
            anchors.fill: parent
            interactive: false
            orientation: Qt.Horizontal
            model: MASTERCONTROLLER.droneModel
            spacing: Theme.standardSpacing
            delegate: StandardText {
                id: droneStatusText
                anchors.verticalCenter: parent.verticalCenter
                color: (drone.globalStatus === SpyC.NOMINAL) ? Theme.nominalColor : (drone.globalStatus === SpyC.WARNING ? Theme.warningColor : Theme.criticalColor)
                text: "[" + drone.uid + " (" + drone.flightStatusText + ")]"
                font.pixelSize: Theme.largeFontSize
                visible: MASTERCONTROLLER.currentDrone !== drone
                width: MASTERCONTROLLER.currentDrone === drone ? 0 : droneStatusText.implicitWidth
            }
        }
    }

    // Thales icon
    Image {
        id: thalesIcon
        anchors.centerIn: parent
        source: "qrc:/images/ico-thales.png"
        height: parent.height
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }

    // Date display
    DateDisplay {
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
    }
}
