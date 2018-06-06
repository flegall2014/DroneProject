import QtQuick 2.5
import "."

Item {
    anchors.fill: parent
    property alias bottomBarContents: bottomBar.children
    property alias dialogContents: contents.children
    property variant targetDrone
    signal closeDialog()
    Item {
        id: contents
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
    }
    Item {
        id: bottomBar
        anchors.bottom: parent.bottom
        width: parent.width
        height: Theme.toolBarHeight
    }
}
