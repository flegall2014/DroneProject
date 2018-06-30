import QtQuick 2.5
import Qt.labs.platform 1.0
import "."
import "./widgets"

Item {
    id: root
    property variant targetDrone
    property bool hasCloseButton: true
    signal closePanel()
    signal fileAccepted(string filePath)

    // Open dialog
    function openDialog(nameFilters, fileMode)
    {
        fileDialog.fileMode = fileMode
        fileDialog.nameFilters = nameFilters
        fileDialog.open()
    }

    // File dialog
    FileDialog {
        id: fileDialog
        onAccepted: root.fileAccepted(fileDialog.file)
    }

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
    property alias panelTitle: panelTitle.text
    property bool blinking: true

    // Panel contents
    property alias panelContents: panelContents.children

    // Left toolbar
    property alias leftToolBarContents: leftToolBarContents.children

    // Right toolbar
    property alias rightToolBarContents: rightToolBarContents.children

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
        Item {
            id: leftToolBarContents
            anchors.left: parent.left
            anchors.leftMargin: Theme.standardMargin
            anchors.right: parent.right
            anchors.rightMargin: Theme.standardMargin
            height: parent.height
        }
        StandardText {
            id: panelTitle
            color: Theme.warningColor
            anchors.centerIn: parent
            font.bold: true
            opacity: blinking ? 0 : 1
            Timer {
                id: timer
                running: blinking && (panelTitle.text.length > 0)
                interval: Theme.blinkTitleBlinkInterval
                repeat: true
                triggeredOnStart: true
                onTriggered: panelTitle.opacity = 1-panelTitle.opacity
            }
            Behavior on opacity {
                NumberAnimation {duration: timer.interval}
            }
        }
        Item {
            id: rightToolBarContents
            anchors.left: panelTitle.right
            anchors.leftMargin: Theme.standardMargin
            anchors.right: hasCloseButton ? closeButton.left : parent.right
            anchors.rightMargin: Theme.standardMargin
            height: parent.height
        }

        // Close button
        ImageButton {
            id: closeButton
            visible: hasCloseButton
            anchors.right: parent.right
            anchors.rightMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/ico-close.svg"
            onClicked: closePanel()
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
