import QtQuick 2.5
import QtQuick.Controls 1.4

Row {
    property alias echoRadioChecked: ecoRadio.checked
    property alias obsRadioChecked: obsRadio.checked
    property alias fastRadioChecked: fastRadio.checked
    signal ecoClicked
    signal obsClicked
    signal fastClicked
    ExclusiveGroup {
        id: exclGroup
    }
    Item {
        width: parent.width/3
        height: parent.height
        StandardRadioButton {
            id: ecoRadio
            anchors.centerIn: parent
            labelText: qsTr("ECO")
            exclusiveGroup: exclGroup
            onClicked: ecoClicked()
        }
    }
    Item {
        width: parent.width/3
        height: parent.height
        StandardRadioButton {
            id: obsRadio
            anchors.centerIn: parent
            labelText: qsTr("OBS")
            exclusiveGroup: exclGroup
            onClicked: obsClicked()
        }
    }
    Item {
        width: parent.width/3
        height: parent.height
        StandardRadioButton {
            id: fastRadio
            anchors.centerIn: parent
            labelText: qsTr("FAST")
            exclusiveGroup: exclGroup
            onClicked: fastClicked()
        }
    }
}
