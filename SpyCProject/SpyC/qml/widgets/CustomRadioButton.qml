import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import ".."

RadioButton {
    id: radioButton

    signal radioButtonClick()

    property int radioButtonWidth: Theme.buttonSize
    property int radioButtonHeight: Theme.buttonSize
    property real labelSize: Theme.veryLargeFontSize
    property color labelColor: Theme.defaultFontColor
    property color borderColor: "transparent"
    property color onHoverColor: "crimson"
    property color normalColor: "lightblue"
    property string labelText: qsTr("Radio Button")

    text: labelText
    style: RadioButtonStyle {
        indicator: Rectangle {
            implicitWidth: Theme.buttonSize
            implicitHeight: Theme.buttonSize
            radius: Theme.buttonSize
            border.color: ( control.activeFocus || control.checked ) ? "green" : "darkblue"
            border.width: 1
            Rectangle {
                anchors.fill: parent
                visible: control.checked
                color: "green"
                radius: Theme.buttonSize
                anchors.margins: Theme.standardMargin/2
            }
        }
        background: Rectangle {
            id: backgroundView
            implicitWidth: radioButtonWidth+4
            implicitHeight: radioButtonHeight+4
            border.width: control.hovered ? 2 : 1
            border.color: control.hovered ? radioButton.onHoverColor : radioButton.borderColor
            color: "transparent" //control.pressed ? Qt.darker( radioButton.normalColor, 1.5 ) : radioButton.normalColor
            Behavior on color { ColorAnimation{ duration: 50 } }
            radius: 6
            scale: control.pressed ? 1.1 : 1.0
            Behavior on scale { NumberAnimation{ duration: 50 } }
        }
        label: Text {
            font.pixelSize: labelSize
            color: labelColor
            text: labelText
            wrapMode: Text.WordWrap
        }
    }

    onClicked: {
        radioButtonClick()
    }
}
