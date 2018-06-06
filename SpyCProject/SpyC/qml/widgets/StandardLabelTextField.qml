import QtQuick 2.5
import ".."

Row {
    width: 192
    height: Theme.standardDelegateHeight
    property alias label: label.text
    property alias text: textField.text
    signal valueChanged(double value)
    StandardText {
        id: label
        text: "Latitude"
        width: 96
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
    }
    StandardTextField {
        id: textField
        width: 96
        height: parent.height
        text: coordinate.latitude.toFixed(3)
        anchors.verticalCenter: parent.verticalCenter
        validator: DoubleValidator {
            bottom: -90
            top: 90
        }
        onAccepted: valueChanged(parseFloat(textField.text))
    }
}
