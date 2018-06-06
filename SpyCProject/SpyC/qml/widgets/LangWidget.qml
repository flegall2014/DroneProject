import QtQuick 2.5
import Components 1.0
import ".."

Row {
    width: french.width+us.width+saudi.width+2*spacing
    height: Theme.buttonSize
    spacing: Theme.standardSpacing
    ImageButton {
        id: french
        source: "qrc:/icons/ico-french-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.language === SpyC.FRENCH
        onClicked: {
            MASTERCONTROLLER.settingController.language = SpyC.FRENCH
        }
    }
    ImageButton {
        id: us
        source: "qrc:/icons/ico-us-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.language === SpyC.ENGLISH
        onClicked: {
            MASTERCONTROLLER.settingController.language = SpyC.ENGLISH
        }
    }
    ImageButton {
        id: saudi
        source: "qrc:/icons/ico-saudi-flag.png"
        checkable: true
        checked: MASTERCONTROLLER.settingController.language === SpyC.ARABIC
        onClicked: {
            MASTERCONTROLLER.settingController.language = SpyC.ARABIC
        }
    }
}
