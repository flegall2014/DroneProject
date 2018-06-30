import QtQuick 2.5
import QtQuick.Controls 2.0
import Components 1.0
import "../.."

// Common area
Rectangle {
    id: commonArea
    color: Theme.backgroundColor
    height: Theme.commonAreaHeight
    property variant targetDrone

    // Panel manager
    PanelManager {
        id: panelMgr
        anchors.fill: parent
        targetDrone: commonArea.targetDrone
    }

    // Load panel
    function loadPanel(panelName)
    {
        panelMgr.onLoadPanel(panelName)
    }

    // Listen to drone flight status changed
    function onDroneFlightStatusChanged()
    {
        if (targetDrone.flightStatus === SpyC.FLYING)
            panelMgr.loadPanel("FlightEditor")
        else
        if (targetDrone.flightStatus === SpyC.IDLE)
            panelMgr.loadPanel("PayloadEditor")
    }

    // Listen to drone work mode changed
    function onWorkModeChanged()
    {
        if (targetDrone.workMode === SpyC.MISSION_PLAN_EDIT)
            panelMgr.loadPanel("MissionPlanEditor")
        else
        if (targetDrone.workMode === SpyC.SAFETY_EDIT)
            panelMgr.loadPanel("SafetyPlanEditor")
        else
        if (targetDrone.workMode === SpyC.LANDING_PLAN_EDIT)
            panelMgr.loadPanel("LandingPlanEditor")
        else
        if (targetDrone.workMode === SpyC.CARTO_EDIT)
            panelMgr.loadPanel("CartoEditor")
        else
        if (targetDrone.workMode === SpyC.PAYLOAD_EDIT)
            panelMgr.loadPanel("PayloadEditor")
        else
        if (targetDrone.workMode === SpyC.GALLERY_EDIT)
            panelMgr.loadPanel("GalleryEditor")
        else
        if (targetDrone.workMode === SpyC.EXCLUSION_EDIT)
            panelMgr.loadPanel("ExclusionAreaEditor")
        else
            panelMgr.loadPanel("PayloadEditor")
    }

    Component.onCompleted: {
        targetDrone.flightStatusChanged.connect(onDroneFlightStatusChanged)
        targetDrone.workModeChanged.connect(onWorkModeChanged)
    }
}
