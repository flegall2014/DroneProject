import QtQuick 2.5
import ".."

StandardButton {
    property alias source: icon.source
    width: Theme.buttonSize
    height: Theme.buttonSize
    Image {
        id: icon
        anchors.fill: parent
        anchors.margins: 3
        sourceSize: Qt.size(width, height)
        fillMode: Image.PreserveAspectFit
    }
}
