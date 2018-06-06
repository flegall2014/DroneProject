import QtQuick 2.5

Rectangle {
    property real pitchAngle:       0
    property real rollAngle:        0
    property real size:             ScreenTools.isAndroid ? 300 : 100
    property real reticleHeight:   1
    property real reticleSpacing:  size * 0.15
    property real reticleSlot:     reticleSpacing + reticleHeight
    property real longDash:        size * 0.35
    property real shortDash:       size * 0.25

    height: size
    width:  size
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter:   parent.verticalCenter
    clip: true
    Item {
        height: parent.height
        width:  parent.width
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter:   parent.verticalCenter
            spacing: reticleSpacing
            Repeater {
                model: 36
                Rectangle {
                    property int pitch: -(modelData * 5 - 90)
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: (pitch % 10) === 0 ? longDash : shortDash
                    height: reticleHeight
                    color: "white"
                    antialiasing: true
                    smooth: true
                    StandardText {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: -(longDash)
                        anchors.verticalCenter: parent.verticalCenter
                        smooth: true
                        text: pitch
                        color: "white"
                        visible: (pitch != 0) && ((pitch % 10) === 0)
                    }
                    StandardText {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: (longDash)
                        anchors.verticalCenter: parent.verticalCenter
                        smooth: true
                        text: pitch
                        color: "white"
                        visible: (pitch != 0) && ((pitch % 10) === 0)
                    }
                }
            }
        }
        transform: [ Translate {
                y: (pitchAngle * reticleSlot / 5) - (reticleSlot / 2)
            }]
    }
    transform: [
        Rotation {
            origin.x: width  / 2
            origin.y: height / 2
            angle:    -rollAngle
        }
    ]
}
