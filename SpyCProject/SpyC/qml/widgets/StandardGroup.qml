import QtQuick 2.5
import ".."

Rectangle {
    color: "transparent"
    border.color: Theme.defaultFontColor
    property alias title: groupTitle.text
    property alias contents: innerContainer.children

    Item {
        id: titleContainer
        width: parent.width
        height: 24
        StandardText {
            id: groupTitle
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Theme.standardMargin
        }
    }

    Item {
        id: innerContainer
        anchors.fill: parent
    }
}
