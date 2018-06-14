import QtQuick 2.5
import QtGraphicalEffects 1.0
import "../.."
import "../../widgets"
import Components 1.0

Rectangle {
    color: "black"
    property alias source: image.source
    signal close()

    Item {
        id: controlPanel
        width: Theme.controlPanelWidth
        height: parent.height

        Rectangle {
            anchors.fill: parent
            anchors.margins: Theme.standardMargin
            color: "transparent"
            border.color: Theme.defaultPanelBorderColor

            Column {
                anchors.centerIn: parent
                width: parent.width-4*Theme.standardMargin
                height: (.9)*parent.height

                Item {
                    width: parent.width
                    height: parent.height/4
                    // Title
                    StandardText {
                        anchors.centerIn: parent
                        font.pixelSize: Theme.largeFontSize
                        text: qsTr("Image Processing")
                    }
                }

                Item {
                    width: parent.width
                    height: parent.height/4
                    // Brightness
                    StandardSlider {
                        id: brightnessControl
                        width: parent.width
                        height: parent.height/2
                        anchors.centerIn: parent
                        title: qsTr("Brightness")
                        minimumValue: -1
                        maximumValue: 1
                        stepSize: 0.001
                        onApply: bc.brightness = value
                    }
                }

                Item {
                    width: parent.width
                    height: parent.height/4
                    // Contrast
                    StandardSlider {
                        id: contrastControl
                        width: parent.width
                        height: parent.height/2
                        anchors.centerIn: parent
                        title: qsTr("Contrast")
                        minimumValue: -1
                        maximumValue: 1
                        stepSize: 0.001
                        onApply: bc.contrast = value
                    }
                }

                Item {
                    width: parent.width
                    height: parent.height/4
                    // Reset
                    StandardButton {
                        label: qsTr("RESET")
                        anchors.centerIn: parent
                        onClicked: {
                            brightnessControl.value = 0
                            contrastControl.value = 0
                        }
                    }
                }
            }
        }
    }

    Item {
        id: imageContainer
        anchors.left: controlPanel.right
        anchors.right: parent.right
        height: parent.height
        // Image
        Image {
            id: image
            width: parent.width
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
        }

        // Brighness and contrast
        BrightnessContrast {
            id: bc
            anchors.fill: image
            source: image
            brightness: 0.5
            contrast: 0.5
        }

        // Close button
        ImageButton {
            anchors.right: parent.right
            anchors.rightMargin: Theme.standardMargin
            anchors.top: parent.top
            anchors.topMargin: Theme.standardMargin
            source: "qrc:/icons/ico-back.svg"
            onClicked: close()
        }
    }
}
