pragma Singleton
import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import "widgets"

Item {
    // Colors
    property color backgroundColor: "#202F42"
    property color statusBarColor: "#202F42"
    property color toolBarColor: "#202F42"
    property color nominalColor: "#00FF01"
    property color warningColor: "orange"
    property color criticalColor: "red"
    property color defaultPanelBkgColor: "#202F42"
    property color defaultPanelBorderColor: "white"
    property color buttonBkgColor: "lightgray"
    property color defaultFontColor: "white"
    property color invertDefaultFontColor: "black"
    property color checkedColor: "red"
    property color disabledColor: "black"
    property color safetyColor: "red"
    property color missionPlanColor: "green"
    property color landingPlanColor: "blue"
    property color videoBkgColor: "black"
    property color defaultButtonColor: "steelblue"
    property color selectedColor: "orange"
    property color exclusionAreaColor: "red"
    property color exclusionAreaBorderColor: "black"
    property color currentSnapShotBorderColor: "orange"
    property color batteryBkgColor: "black"

    // Sizes
    property int toolBarWidth: 64
    property int toolBarHeight: 64
    property int controlPanelWidth: 316
    property int commonAreaHeight: 316
    property int buttonSize: toolBarHeight-8
    property int sliderSize: toolBarHeight/2
    property int alertDeleagateHeight: 32
    property int mapOrVideoThumbnailSize: 256
    property int goNextIconSize: 160
    property int standardDelegateHeight: 48
    property int busyIndicatorSize: 64
    property int coordinateDelegateHeight: buttonSize
    property int galleryViewToolBarHeight: 32

    // Opacities
    property double exclusionAreaOpacity: .5

    // Font
    property string standardFont: "Segoe UI"
    property int standardFontSize: 14
    property int veryLargeFontSize: 36
    property int largeFontSize: 18
    property int mediumFontSize: 13
    property int smallFontSize: 12

    // Animation
    property int standardAnimationDuration: 300
    property int blinkTitleBlinkInterval: 1000
    property int shapeBlinkInterval: 250

    // Margins
    property int standardMargin: 4
    property int standardSpacing: 8

    // Z
    property int zMax: 1000

    // Tab view style (control panel)
    property Component controlPanelTabViewStyle: TabViewStyle {
        frameOverlap: 1
        tab: Rectangle {
            color: styleData.selected ? "steelblue" : "lightsteelblue"
            border.color:  "steelblue"
            implicitWidth: Math.max(text1.width + 4, 80)
            implicitHeight: 48
            radius: 2
            Text {
                id: text1
                anchors.centerIn: parent
                text: styleData.title
                color: styleData.selected ? Theme.defaultFontColor : Theme.invertDefaultFontColor
            }
        }
        frame: Rectangle { color: "steelblue" }
    }

    // Tab view style (login page)
    property Component loginPageTabViewStyle: TabViewStyle {
        frameOverlap: 1
        tab: Rectangle {
            color: backgroundColor
            border.color:  "steelblue"
            implicitWidth: Math.max(text2.width + 8, 120)
            implicitHeight: buttonSize
            radius: 2
            StandardText {
                id: text2
                anchors.centerIn: parent
                text: styleData.title
                font.pixelSize: veryLargeFontSize
                color: styleData.selected ? Theme.defaultFontColor : Theme.invertDefaultFontColor
            }
        }
        frame: Rectangle { color: backgroundColor }
    }

    // Busy indicator style
    property Component busyIndicatorSytle: BusyIndicatorStyle {
        indicator: Image {
            visible: control.running
            source: "qrc:/icons/ico-spinner.svg"
            width: busyIndicatorSize
            height: busyIndicatorSize
            fillMode: Image.PreserveAspectFit
            RotationAnimator on rotation {
                running: control.running
                loops: Animation.Infinite
                duration: 2000
                from: 0 ; to: 360
            }
        }
    }

}
