import QtQuick 2.5
import "../widgets"
import ".."

// Index delegate
Item {
    id: indexDelegate
    property alias text: label.text
    property alias color: label.color
    signal itemClicked
    Rectangle {
        anchors.fill: parent
        color: Theme.backgroundColor
    }
    StandardText {
        id: label
        anchors.centerIn: parent
        text: wayPointIndex
    }
    Rectangle {
        anchors.right: parent.right
        height: parent.height
        width: 1
        color: "green"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: itemClicked()
    }
}
