import QtQuick 2.5
import ".."

Rectangle {
    id: button
    signal clicked
    width: Theme.buttonSize
    height: Theme.buttonSize
    radius: 5
    border.color: enabled ? (checkable ? (checked ? Theme.checkedColor : Theme.disabledColor) : Theme.disabledColor) : Theme.invertDefaultFontColor
    border.width: checkable ? (checked ? 3 : 1) : 1
    property string label: ""
    antialiasing: true
    property color startColor: "white"
    property color endColor: Theme.defaultButtonColor
    property string textColor: Theme.invertDefaultFontColor
    property bool checkable: false
    property bool checked: false
    property string textPosition: "centered"

    // Gradient
    gradient: Gradient {
        GradientStop { position: 0.0; color: startColor }
        GradientStop { position: 1.0; color: endColor }
    }

    // Label
    StandardText {
        id: titleBelow
        visible: textPosition === "below" && text.length > 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        width: parent.width
        color: textColor
        text: button.label
    }

    // Label
    StandardText {
        id: titleCentered
        visible: textPosition === "centered" && text.length > 0
        anchors.centerIn: parent
        width: parent.width
        color: textColor
        text: button.label
    }

    // Disable mask
    Rectangle {
        color: Theme.disabledColor
        anchors.fill: parent
        radius: parent.radius
        opacity: button.enabled === false ? .45 : 0
        Behavior on opacity {
            NumberAnimation {duration: Theme.standardAnimationDuration}
        }
    }

    // Handle clicks
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    // Define states
    states: State {
        name: "pressed"
        when: checkable ? checked : mouseArea.pressed
        PropertyChanges {
            target: button
            scale: .95
        }
    }
}
