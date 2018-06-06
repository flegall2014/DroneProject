import QtQuick 2.5
import QtQuick.Controls 1.4
import Components 1.0
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0
    property bool goNextEnabled: (armyStandardTextField.text.length > 0) && (unitStandardTextField.text.length > 0) &&
             (missionStandardTextField.text.length > 0) && (operatorStandardTextField.text.length > 0)
    property alias armyText: armyStandardTextField.text
    property alias unitText: unitStandardTextField.text
    property alias missionText: missionStandardTextField.text
    property alias operatorText: operatorStandardTextField.text
    signal loginClicked()

    // Main container
    Rectangle {
        id: mainContainer
        width: parent.width
        height: parent.height-2*Theme.toolBarHeight
        anchors.centerIn: parent
        color: "transparent"
        radius: 8
        border.color: "white"

        Item {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin*2

            // Mission or replay?
            Item {
                id: missionOrReplayGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: parent.top
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                // Exclusive group
                ExclusiveGroup {
                    id: group
                }

                // Mission
                CustomRadioButton {
                    exclusiveGroup: group
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    labelText: qsTr("Mission") + TRANSLATOR.emptyString
                    checked: true
                }

                // Replay
                CustomRadioButton {
                    exclusiveGroup: group
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    labelText: qsTr("Replay") + TRANSLATOR.emptyString
                }
            }

            // Army
            Item {
                id: armyGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: missionOrReplayGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: armyTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Army") + TRANSLATOR.emptyString
                    width: 224
                }
                StandardTextField {
                    id: armyStandardTextField
                    horizontalAlignment: Text.AlignLeft
                    anchors.left: armyTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.army
                    onTextChanged: MASTERCONTROLLER.settingController.army = text
                }
            }

            // Unit
            Item {
                id: unitGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: armyGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: unitTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Unit") + TRANSLATOR.emptyString
                    width: 224
                }
                StandardTextField {
                    id: unitStandardTextField
                    horizontalAlignment: Text.AlignLeft
                    anchors.left: unitTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.unit
                    onTextChanged: MASTERCONTROLLER.settingController.unit = text
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: unitGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: missionTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Mission") + TRANSLATOR.emptyString
                    width: 224
                }
                StandardTextField {
                    id: missionStandardTextField
                    horizontalAlignment: Text.AlignLeft
                    anchors.left: missionTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.mission
                    onTextChanged: MASTERCONTROLLER.settingController.mission = text
                }
            }

            // Operator
            Item {
                id: operatorGroup
                width: parent.width
                height: Theme.buttonSize
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter
                StandardText {
                    id: operatorTitle
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Theme.veryLargeFontSize
                    text: qsTr("Operator") + TRANSLATOR.emptyString
                    width: 224
                }
                StandardTextField {
                    id: operatorStandardTextField
                    horizontalAlignment: Text.AlignLeft
                    anchors.left: operatorTitle.right
                    anchors.right: parent.right
                    height: parent.height
                    font.pixelSize: Theme.veryLargeFontSize
                    text: MASTERCONTROLLER.settingController.operatorName
                    onTextChanged: MASTERCONTROLLER.settingController.operatorName = text
                }
            }
        }
    }
}
