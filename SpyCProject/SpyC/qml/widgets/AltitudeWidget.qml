import QtQuick 2.5
import QtGraphicalEffects 1.0

Item {
    id: root

    property bool showPitch: true
    property real size
    property bool showHeading: true

    property real rollAngle: 0
    property real pitchAngle: 360
    property real heading

    Timer {
        id: timer
        interval: 10
        repeat: true
        running: true
        onTriggered: {
            rollAngle += 1
            pitchAngle -= 1
        }
    }

    width:  size
    height: size

    Item {
        id:             instrument
        anchors.fill:   parent
        visible:        false

        //----------------------------------------------------
        //-- Artificial Horizon
        ArtificialHorizonWidget {
            rollAngle:          rollAngle
            pitchAngle:         pitchAngle
            anchors.fill:       parent
        }
        //----------------------------------------------------
        //-- Pointer
        Image {
            id:                 pointer
            source:             "qrc:/images/img-attitude-pointer.svg"
            mipmap:             true
            fillMode:           Image.PreserveAspectFit
            anchors.fill:       parent
            sourceSize.height:  parent.height
        }
        //----------------------------------------------------
        //-- Instrument Dial
        Image {
            id:                 instrumentDial
            source:             "qrc:/images/img-altitude-dial.svg"
            mipmap:             true
            fillMode:           Image.PreserveAspectFit
            anchors.fill:       parent
            sourceSize.height:  parent.height
            transform: Rotation {
                origin.x:       root.width  / 2
                origin.y:       root.height / 2
                angle:          -rollAngle
            }
        }
        //----------------------------------------------------
        //-- Pitch
        PitchIndicator {
            id:                 pitchWidget
            visible:            root.showPitch
            size:               root.size * 0.5
            anchors.verticalCenter: parent.verticalCenter
            pitchAngle:         pitchAngle
            rollAngle:          rollAngle
            color:              Qt.rgba(0,0,0,0)
        }
        //----------------------------------------------------
        //-- Cross Hair
        Image {
            id:                 crossHair
            anchors.centerIn:   parent
            source:             "qrc:/images/img-cross-hair.svg"
            mipmap:             true
            width:              size * 0.75
            sourceSize.width:   width
            fillMode:           Image.PreserveAspectFit
        }
    }

    Rectangle {
        id:             mask
        anchors.fill:   instrument
        radius:         width / 2
        color:          "black"
        visible:        false
    }

    OpacityMask {
        anchors.fill: instrument
        source: instrument
        maskSource: mask
    }

    Rectangle {
        id:             borderRect
        anchors.fill:   parent
        radius:         width / 2
        color:          Qt.rgba(0,0,0,0)
        border.color:   "black"
        border.width:   2
    }

    StandardText {
        anchors.bottomMargin:       Math.round(font.pixelSize * .75)
        anchors.bottom:             parent.bottom
        anchors.horizontalCenter:   parent.horizontalCenter
        text:                       headingString3
        color:                      "white"
        visible:                    showHeading

        property string headingString: heading.toFixed()
        property string headingString2: headingString.length === 1 ? "0" + headingString : headingString
        property string headingString3: headingString2.length === 2 ? "0" + headingString2 : headingString2
    }
}
