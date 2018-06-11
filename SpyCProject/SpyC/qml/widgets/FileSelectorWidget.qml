import QtQuick 2.5
import QtQuick.Controls 1.4
import Qt.labs.platform 1.0
import Components 1.0
import ".."

Item {
    property alias title: label.text
    height: Theme.buttonSize
    property alias folder: folderDialog.folder
    property alias selectedFolder: input.text

    FolderDialog {
        id: folderDialog
        folder: HELPER.applicationDir()
        onAccepted: {
            input.text = HELPER.toLocalFile(folderDialog.folder)
        }
    }
    StandardText {
        id: label
        anchors.left: parent.left
        horizontalAlignment: Text.AlignLeft
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: Theme.veryLargeFontSize
        text: qsTr("Gallery")
        width: 224
    }
    StandardTextField {
        id: input
        horizontalAlignment: Text.AlignLeft
        anchors.left: label.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: selectButton.left
        anchors.rightMargin: 2*Theme.standardMargin
        height: parent.height
        font.pixelSize: Theme.largeFontSize
        enabled: false
    }
    ImageButton {
        id: selectButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/ico-open.svg"
        onClicked: folderDialog.visible = true
    }
}
