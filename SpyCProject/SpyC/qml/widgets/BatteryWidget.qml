import QtQuick 2.5
import ".."

Item {
    property int currentLevel: 0
    property alias model: listView.model
    property color batteryColor: "green"
    property int cellCount: 10
    property int cellSize: 12
    width: cellSize*cellCount+percentText.width+8
    height: cellSize
    Rectangle {
        width: cellSize*cellCount
        height: parent.height
        color: "transparent"
        border.color: "white"
        Item {
            anchors.fill: parent
            anchors.margins: 1
            Rectangle {
                width: currentLevel*parent.width/100
                height: parent.height
                color: batteryColor
            }
        }
    }
    ListView {
        id: listView
        orientation: Qt.Horizontal
        interactive: false
        width: cellSize*cellCount
        height: parent.height
        model: cellCount
        delegate: Item {
            width: cellSize
            height: cellSize
            Rectangle {
                width: 1
                height: parent.height
                anchors.right: parent.right
                border.color: "white"
                visible: index < (cellCount-1)
            }
        }
    }

    StandardText {
        id: percentText
        anchors.left: listView.right
        anchors.leftMargin: Theme.standardMargin
        anchors.verticalCenter: parent.verticalCenter
        text: currentLevel + "%"
    }
}
