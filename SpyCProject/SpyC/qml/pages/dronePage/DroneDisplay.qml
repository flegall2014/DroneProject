import QtQuick 2.5
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../../widgets"
import "../.."

Rectangle {
    id: droneDisplay
    border.color: (targetDrone.globalStatus === SpyC.NOMINAL) ? Theme.nominalColor : (targetDrone.globalStatus === SpyC.WARNING ? Theme.warningColor : Theme.criticalColor)
    border.width: 3
    color: Theme.backgroundColor
    property variant targetDrone

    // Flip
    function flip()
    {
        flipable.state = "back"
    }

    Item {
        anchors.fill: parent
        anchors.margins: parent.border.width

        // Common area
        CommonArea {
            id: commonArea
            height: 0
            opacity: 0
            anchors.bottom: parent.bottom
            width: parent.width
            targetDrone: drone
        }

        // Control Panel
        ControlPanel {
            id: controlPanel
            width: 0
            opacity: 0
            anchors.right: MASTERCONTROLLER.settingController.hand === SpyC.RIGHT_HAND ? parent.right : undefined
            anchors.left: MASTERCONTROLLER.settingController.hand === SpyC.LEFT_HAND ? parent.left : undefined
            anchors.bottom: commonArea.top
            anchors.top: parent.top
            targetDrone: drone
            onTakeSnapShot: videoView.takeSnapShot()
        }

        Item {
            id: root
            anchors.left: MASTERCONTROLLER.settingController.hand === SpyC.RIGHT_HAND ? parent.left : controlPanel.right
            anchors.right: MASTERCONTROLLER.settingController.hand === SpyC.RIGHT_HAND ? controlPanel.left : parent.right
            anchors.bottom: commonArea.top
            anchors.top: parent.top

            Item {
                id: topContainer
                width: parent.width
                height: Theme.toolBarHeight
                visible: MASTERCONTROLLER.currentDrone === null

                // Drone status widget
                DroneStatusWidget {
                    id: droneStatusWidget
                    anchors.left: parent.left
                    anchors.right: unlockButton.left
                    height: Theme.toolBarHeight
                    targetDrone: drone
                    opacity: 1
                    visible: opacity > 0
                }

                // Unlock
                ImageButton {
                    id: unlockButton
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/icons/ico-edit.svg"
                    Behavior on opacity {
                        NumberAnimation {duration: Theme.standardAnimationDuration}
                    }
                    onClicked: {
                        if (MASTERCONTROLLER.currentDrone === null)
                            MASTERCONTROLLER.currentDrone = targetDrone
                        else
                            MASTERCONTROLLER.currentDrone = null
                    }
                }
            }

            Flipable {
                id: flipable
                width: parent.width
                anchors.top: topContainer.visible ? topContainer.bottom : parent.top
                anchors.bottom: parent.bottom

                // Define transform
                transform: Rotation {
                    id: rotation
                    origin.x: flipable.width/2
                    origin.y: flipable.height/2
                    axis.x: 1; axis.y: 0; axis.z: 0
                    angle: 0
                }

                // Define states
                states: State {
                    name: "back"
                    PropertyChanges {target: rotation; angle: 180}
                    when: flipable.flipped
                }

                transitions: Transition {
                    NumberAnimation {target: rotation; property: "angle"; duration: 2*Theme.standardAnimationDuration}
                }

                // Map & Video views
                front: Item {
                    width: parent.width
                    height: parent.height

                    // Map view
                    MapView {
                        id: mapView
                        width: parent.width
                        height: parent.height/2
                        z: 0
                        targetDrone: drone
                    }

                    // Horizontal toolbar loader
                    Loader {
                        id: horizontalToolBarLoader
                        width: parent.width
                        height: Theme.toolBarHeight
                        z: Theme.zMax
                        anchors.top: parent.top
                        onLoaded: item.targetDrone = targetDrone
                        function onWorkModeChanged()
                        {
                            if (targetDrone.workMode === SpyC.MISSION_PLAN_EDIT)
                                horizontalToolBarLoader.source = "qrc:/qml/toolbars/MissionPlanToolBar.qml"
                            else
                                if (targetDrone.workMode === SpyC.SAFETY_EDIT)
                                    horizontalToolBarLoader.source =  "qrc:/qml/toolbars/SafetyToolBar.qml"
                                else
                                    if (targetDrone.workMode === SpyC.LANDING_PLAN_EDIT)
                                        horizontalToolBarLoader.source =  "qrc:/qml/toolbars/LandingPlanToolBar.qml"
                                    else
                                        if (targetDrone.workMode === SpyC.EXCLUSION_EDIT)
                                            horizontalToolBarLoader.source =  "qrc:/qml/toolbars/ExclusionAreaToolBar.qml"
                                        else
                                            horizontalToolBarLoader.source = ""
                        }
                        Component.onCompleted: targetDrone.workModeChanged.connect(onWorkModeChanged)
                    }

                    // Video view
                    VideoView {
                        id: videoView
                        targetDrone: drone
                        x: 0
                        y: mapView.height
                        z: 0
                        width: parent.width
                        height: parent.height/2
                    }

                    // Swith carto/video
                    ImageButton {
                        id: switchButton
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.standardMargin
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: Theme.standardMargin
                        source: "qrc:/icons/ico-swap.svg"
                        visible: (MASTERCONTROLLER.currentDrone !== null) && (targetDrone === MASTERCONTROLLER.currentDrone)
                        onClicked: {
                            if (droneDisplay.state === "map_maximized")
                                droneDisplay.state = "map_minimized"
                            else
                                if (droneDisplay.state === "map_minimized")
                                    droneDisplay.state = "map_maximized"
                            if (MASTERCONTROLLER.currentDrone !== null)
                                MASTERCONTROLLER.currentDrone.setDefaultWorkMode
                        }
                    }
                }

                // Image view
                back: ImageView {
                    width: parent.width
                    height: parent.height
                    source: HELPER.fromLocalFile(targetDrone.galleryModel.currentScreenCapPath)
                    onClose: flipable.state = ""
                }
            }
        }
    }

    // States
    states: [
        State {
            name: "map_maximized"
            PropertyChanges {
                target: commonArea
                height: Theme.commonAreaHeight
                opacity: 1
            }
            PropertyChanges {
                target: controlPanel
                width: Theme.controlPanelWidth
                opacity: 1
            }
            PropertyChanges {
                target: droneDisplay
                width: dronePage.width
            }
            PropertyChanges {
                target: dronePage
                explicit: true
                contentX: droneDisplay.x
            }
            PropertyChanges {
                target: droneStatusWidget
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: mapView
                width: root.width
                height: parent.height
                x: 0
                y: 0
                z: 0
            }
            PropertyChanges {
                target: videoView
                width: Theme.mapOrVideoThumbnailSize
                height: Theme.mapOrVideoThumbnailSize
                x: mapView.width-Theme.mapOrVideoThumbnailSize
                y: mapView.height-Theme.mapOrVideoThumbnailSize
                z: Theme.zMax
            }
        },
        State {
            name: "map_minimized"
            PropertyChanges {
                target: commonArea
                height: Theme.commonAreaHeight
                opacity: 1
            }
            PropertyChanges {
                target: controlPanel
                width: Theme.controlPanelWidth
                opacity: 1
            }
            PropertyChanges {
                target: droneDisplay
                width: dronePage.width
            }
            PropertyChanges {
                target: dronePage
                explicit: true
                contentX: droneDisplay.x
            }
            PropertyChanges {
                target: droneStatusWidget
                height: 0
                opacity: 0
            }
            PropertyChanges {
                target: mapView
                width: Theme.mapOrVideoThumbnailSize
                height: Theme.mapOrVideoThumbnailSize
                x: videoView.width-Theme.mapOrVideoThumbnailSize
                y: videoView.height-Theme.mapOrVideoThumbnailSize
                z: Theme.zMax
            }
            PropertyChanges {
                target: videoView
                width: root.width
                height: parent.height
                x: 0
                y: 0
                z: 0
            }
        }
    ]

    transitions: Transition {
        // Make the state changes smooth
        NumberAnimation {
            duration: Theme.standardAnimationDuration
            properties: "x, y, width, height, contentX, opacity"
        }
    }

    // Current drone changed
    function onCurrentDroneChanged()
    {
        if (MASTERCONTROLLER.currentDrone !== null)
        {
            if (targetDrone === MASTERCONTROLLER.currentDrone)
                droneDisplay.state = "map_maximized"
        }
        else
        {
            flipable.state = ""
            droneDisplay.state = ""
        }
    }

    Component.onCompleted: MASTERCONTROLLER.currentDroneChanged.connect(onCurrentDroneChanged)
}
