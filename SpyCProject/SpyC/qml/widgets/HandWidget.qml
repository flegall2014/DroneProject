import QtQuick 2.5
import Components 1.0
import ".."

Row {
    width: leftHand.width+rightHand.width
    height: Theme.buttonSize
    spacing: Theme.standardSpacing
    ImageButton {
        id: leftHand
        source: "qrc:/icons/ico-right-hand.svg"
        checkable: true
        checked: MASTERCONTROLLER.settingController.hand === SpyC.LEFT_HAND
        onClicked: MASTERCONTROLLER.settingController.hand = SpyC.LEFT_HAND
        transform: Rotation {
            id: rot
            origin.x: leftHand.width/2
            origin.y: leftHand.height/2
            axis.x:0; axis.y:1; axis.z:0
            angle: 180
        }
    }
    ImageButton {
        id: rightHand
        source: "qrc:/icons/ico-right-hand.svg"
        checkable: true
        checked: MASTERCONTROLLER.settingController.hand === SpyC.RIGHT_HAND
        onClicked: MASTERCONTROLLER.settingController.hand = SpyC.RIGHT_HAND
    }
}
