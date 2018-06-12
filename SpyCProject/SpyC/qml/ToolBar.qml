import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import "."
import "./widgets"

// Status bar
Rectangle {
    id: toolBar
    color: Theme.toolBarColor
    property bool showDroneStatus: false
    property alias mainTitle: mainTitle.text

    // Drone status widget
    DroneStatusWidget {
        id: droneStatusWidget
        width: toolBar.width-mainTitle.width-64
        anchors.right: mainTitle.left
        height: parent.height
        opacity: showDroneStatus ? 1 : 0
        visible: opacity > 0
        targetDrone: MASTERCONTROLLER.currentDrone
        function onDroneReady()
        {
            if ((typeof MASTERCONTROLLER.currentDrone !== "undefined") && (MASTERCONTROLLER.currentDrone !== null))
                droneStatusWidget.targetDrone = MASTERCONTROLLER.currentDrone
        }
        Component.onCompleted: MASTERCONTROLLER.currentDroneChanged.connect(onDroneReady)
        Behavior on opacity {
            NumberAnimation {duration: Theme.standardAnimationDuration}
        }
    }

    // Main title
    StandardText {
        id: mainTitle
        anchors.centerIn: MASTERCONTROLLER.currentDrone !== null ? undefined : parent
        anchors.right: MASTERCONTROLLER.currentDrone !== null ? quitButton.left : undefined
        anchors.rightMargin: Theme.standardMargin
        font.pixelSize: Theme.largeFontSize
        font.bold: true
    }

    // Quit button
    ImageButton {
        id: quitButton
        anchors.right: parent.right
        anchors.rightMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-shutdown.png"
        onClicked: dialogMgr.showDialog(SpyC.EXIT_SPYC)
    }
}
