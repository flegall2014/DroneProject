import QtQuick 2.4
import Components 1.0
import ".."
import "../widgets"

DialogBase {
    bottomBarContents: Item {
        anchors.fill: parent

        // Cancel
        StandardButton {
            id: cancelButton
            anchors.right: parent.right
            anchors.rightMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            label: qsTr("Cancel")
            onClicked: {
                closeDialog()
            }
        }

        // OK
        StandardButton {
            id: okButton
            anchors.right: cancelButton.left
            anchors.rightMargin: Theme.standardMargin
            anchors.verticalCenter: parent.verticalCenter
            label: qsTr("OK")
            onClicked: {
                targetDrone.galleryModel.clear()
                targetDrone.setDefaultWorkMode()
                closeDialog()
            }
        }
    }
    dialogContents: Item {
        anchors.fill: parent
        StandardText {
            anchors.centerIn: parent
            font.pixelSize: Theme.largeFontSize
            text: qsTr("Confirm clear gallery?")
        }
    }
}

