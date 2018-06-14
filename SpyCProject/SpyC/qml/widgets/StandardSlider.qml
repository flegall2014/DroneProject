import QtQuick 2.0
import QtQuick.Controls 1.4
import ".."
import "../widgets"

Item {
    property alias minimumValue: slider.minimumValue
    property alias maximumValue: slider.maximumValue
    property alias stepSize: slider.stepSize
    property alias value: slider.value
    property string title
    signal apply(real value)
    StandardText {
        id: label
        width: parent.width
        text: title + " (" + slider.value.toFixed(3) + ") "
    }
    Slider {
        id: slider
        width: parent.width
        height: Theme.sliderSize
        anchors.top: label.bottom
        anchors.topMargin: Theme.standardMargin
        onValueChanged: apply(value)
    }
}
