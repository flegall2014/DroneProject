import QtQuick 2.5
import "."
import "./widgets"

Item {
    id: root
    property variant targetDrone

    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    // Background
    Rectangle {
        anchors.fill: parent
        color: Theme.defaultPanelBkgColor
    }

    // Panel title
    property alias title: panelTitle.text

    // Central title
    property alias centralTitle: statusText.text

    // Panel contents
    property alias panelContents: panelContents.children

    // Toolbar contents
    property alias toolBarContents: toolBarContents.children

    // Panel object object (from JSON)
    property variant panelObject

    // Toolbar area
    Rectangle {
        id: panelToolbar
        color: "transparent"
        border.color: Theme.defaultPanelBorderColor
        anchors.top: parent.top
        width: parent.width
        height: Theme.toolBarHeight
        StandardText {
            id: panelTitle
            width: Theme.panelTitleWidth
            anchors.left: parent.left
            anchors.leftMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignLeft
        }
        StandardText {
            id: statusText
            color: Theme.warningColor
            anchors.centerIn: parent
            font.bold: true
            opacity: 0
            Timer {
                id: timer
                running: statusText.text.length > 0
                interval: Theme.centralTitleBlinkInterval
                repeat: true
                triggeredOnStart: true
                onTriggered: statusText.opacity = 1-statusText.opacity
            }
            Behavior on opacity {
                NumberAnimation {duration: timer.interval}
            }
        }
        Item {
            id: toolBarContents
            anchors.left: statusText.right
            anchors.right: parent.right
            height: parent.height
        }
    }

    // Panel contents
    Item {
        id: panelContents
        width: parent.width
        anchors.top: panelToolbar.bottom
        anchors.bottom: parent.bottom
    }

    // Initialize panel (virtual)
    function initialize()
    {
        title = panelObject.displayName
    }

    // Finalize panel (virtual)
    function finalize()
    {
    }
}
