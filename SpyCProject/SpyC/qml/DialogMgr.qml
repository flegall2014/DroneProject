import QtQuick 2.5
import Components 1.0
import "."
import "./widgets"

Item {
    id: root
    opacity: 0
    visible: opacity > 0
    property int msgType: SpyC.INFORMATION_MSG

    function showDialog(dialogType, droneUID)
    {
        root.state = "active"
        if (dialogType === SpyC.CONFIRM_ARM)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmArmDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.CONFIRM_TAKE_OFF)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmTakeOffDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.CONFIRM_FAILSAFE)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmFailSafeDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.CONFIRM_GO_HOME)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmGoHomeDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.EMPTY_MISSION_PLAN_ERROR)
        {
            dialogLoader.source = "qrc:/qml/dialogs/EmptyMissionPlanErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.EMPTY_SAFETY_PLAN_ERROR)
        {
            dialogLoader.source = "qrc:/qml/dialogs/EmptySafetyPlanErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.EMPTY_LANDING_PLAN_ERROR)
        {
            dialogLoader.source = "qrc:/qml/dialogs/EmptyLandingPlanErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.MISSION_PLAN_VALIDATION)
        {
            dialogLoader.source = "qrc:/qml/dialogs/MissionPlanValidationDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.NOT_ENOUGH_POINT_IN_MISSION_PLAN)
        {
            dialogLoader.source = "qrc:/qml/dialogs/NotEnoughPointInMissionPlanErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.NOT_ENOUGH_POINT_IN_SAFETY)
        {
            dialogLoader.source = "qrc:/qml/dialogs/NotEnoughPointInSafetyErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.SAFETY_VALIDATION)
        {
            dialogLoader.source = "qrc:/qml/dialogs/SafetyValidationDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.NO_EXCLUSION_AREA_ERROR)
        {
            dialogLoader.source = "qrc:/qml/dialogs/NoExclusionAreaErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.EXCLUSION_AREA_VALIDATION)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ExclusionAreaValidationDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.CONFIRM_REMOVE_CAPTURE)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmRemoveCaptureDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.CONFIRM_CLEAR_GALLERY)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmClearGalleryDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.LANDING_PLAN_VALIDATION)
        {
            dialogLoader.source = "qrc:/qml/dialogs/LandingPlanValidationDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.UNEXPECTED_LANDING_PLAN_COUNT_ERROR)
        {
            dialogLoader.source = "qrc:/qml/dialogs/UnexpectedLandingPlanCountErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.EMPTY_EXCLUSION_AREA)
        {
            dialogLoader.source = "qrc:/qml/dialogs/UnexpectedLandingPlanCountErrorDialog.qml"
            root.msgType = SpyC.CRITICAL_MSG
        }
        else
        if (dialogType === SpyC.GOHOME_INFLYINGMODE_ONLY)
        {
            dialogLoader.source = "qrc:/qml/dialogs/GoHomeOnlyInFlyingModeErrorDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
        else
        if (dialogType === SpyC.EXIT_SPYC)
        {
            dialogLoader.source = "qrc:/qml/dialogs/ConfirmExitSpyCDialog.qml"
            root.msgType = SpyC.INFORMATION_MSG
        }
    }

    // Background
    Rectangle {
        id: bkg
        color: "gray"
        opacity: .25
        anchors.fill: parent
    }

    // Dialog container
    Rectangle {
        width: 540
        height: 384
        color: Theme.backgroundColor
        border.color: msgType === SpyC.INFORMATION_MSG ? Theme.nominalColor : (msgType === SpyC.WARNING_MSG ? Theme.warningColor : Theme.criticalColor)
        border.width: 3
        radius: 8
        anchors.centerIn: parent

        // Title area
        Rectangle {
            id: titleArea
            width: parent.width
            height: Theme.toolBarHeight
            property color titleBkgColor: msgType === SpyC.INFORMATION_MSG ? Theme.nominalColor : (msgType === SpyC.WARNING_MSG ? Theme.warningColor : Theme.criticalColor)

            // Gradient
            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 1.0; color: titleArea.titleBkgColor }
            }

            // Title
            StandardText {
                text: qsTr("Spy'C messenger")
                font.pixelSize: Theme.largeFontSize
                anchors.left: parent.left
                anchors.leftMargin: Theme.standardMargin
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
                color: Theme.invertDefaultFontColor
            }

            // Close button
            ImageButton {
                anchors.right: parent.right
                anchors.rightMargin: Theme.standardMargin
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/icons/ico-close.svg"
                onClicked: root.state = ""
            }
        }

        // Dialog loader
        Loader {
            id: dialogLoader
            width: parent.width
            anchors.top: titleArea.bottom
            anchors.bottom: parent.bottom
            onLoaded: {
                item.targetDrone = MASTERCONTROLLER.currentDrone
                item.closeDialog.connect(onCloseDialog)
            }
        }
    }

    // Close dialog
    function onCloseDialog()
    {
        root.state = ""
        dialogLoader.source = ""
    }

    // States
    states: State {
        name: "active"
        PropertyChanges {
            target: root
            opacity: 1
        }
    }

    // Transition
    transitions: Transition {
        // Make the state changes smooth
        NumberAnimation {
            duration: 300
            properties: "opacity"
        }
    }
}
