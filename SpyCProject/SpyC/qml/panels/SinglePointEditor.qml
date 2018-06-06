import QtQuick 2.5
import QtQuick.Layouts 1.2
import "../widgets"
import ".."

Item {
    id: pointEditor
    Rectangle {
        anchors.fill: parent
        anchors.margins: Theme.standardMargin
        color: Theme.backgroundColor
        border.color: "green"
        Item {
            width: parent.width
            height: Theme.toolBarHeight
            anchors.top: parent.top
            ImageButton {
                source: "qrc:/icons/ico-point.svg"
                anchors.left: parent.left
                anchors.leftMargin: Theme.standardMargin
                anchors.verticalCenter: parent.verticalCenter
            }
            ImageButton {
                source: "qrc:/icons/ico-circle.svg"
                anchors.centerIn: parent
            }
            ImageButton {
                source: "qrc:/icons/ico-hippodrom.svg"
                anchors.right: parent.right
                anchors.rightMargin: Theme.standardMargin
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
