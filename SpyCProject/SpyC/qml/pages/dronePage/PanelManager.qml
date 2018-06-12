import QtQuick 2.5
import QtQuick.Controls 1.4
import "../.."

StackView {
    id: panelMgr

    // Target drone
    property variant targetDrone

    // Depth changed
    onDepthChanged: console.log("--- DEPTH --- " + depth)

    // Loadp panel
    signal loadPanel(string panelId)

    // Vertical transition
    delegate: StackViewDelegate {

        function transitionFinished(properties)
        {
            properties.exitItem.opacity = 1
        }

        pushTransition: StackViewTransition {
            PropertyAnimation {
                target: enterItem
                property: "y"
                from: target.height
                to: 0
                duration: Theme.standardAnimationDuration
            }
            PropertyAnimation {
                target: exitItem
                property: "y"
                from: 0
                to: target.height
                duration: Theme.standardAnimationDuration
            }
        }
    }

    // Panels
    property variant panels: [
        {
            "name": "MissionPlanEditor",
            "displayName": "Mission Plan Editor",
            "url": "qrc:/qml/panels/MissionPlanEditorPanel.qml"
        },
        {
            "name": "SafetyPlanEditor",
            "displayName": "Safety Plan Editor",
            "url": "qrc:/qml/panels/SafetyPlanEditorPanel.qml"
        },
        {
            "name": "LandingPlanEditor",
            "displayName": "Landing Plan Editor",
            "url": "qrc:/qml/panels/LandingPlanEditorPanel.qml"
        },
        {
            "name": "PayloadEditor",
            "displayName": "Payload Editor",
            "url": "qrc:/qml/panels/PayloadEditorPanel.qml"
        },
        {
            "name": "FlightEditor",
            "displayName": "Flight Editor",
            "url": "qrc:/qml/panels/FlightEditorPanel.qml"
        },
        {
            "name": "GalleryEditor",
            "displayName": "Gallery Editor",
            "url": "qrc:/qml/panels/GalleryEditorPanel.qml"
        },
        {
            "name": "ExclusionAreaEditor",
            "displayName": "Exclusion Area",
            "url": "qrc:/qml/panels/ExclusionAreaEditorPanel.qml"
        }
    ]

    // Get panel object
    function getPanelObject(name)
    {
        for (var i=0; i<panels.length; i++)
        {
            var panelObject = panels[i]
            if ((typeof panelObject !== "undefined") && (panelObject !== null))
            {
                if (panelObject.name === name)
                    return panelObject
            }
        }
        return null
    }

    // Create panel
    function createPanel(panelIdentifier)
    {
        // Get panel description
        var panelObject = getPanelObject(panelIdentifier)
        if (!panelObject) {
            console.log("CAN'T GET PANEL: " + panelIdentifier)
            return null
        }

        // Create a new panel component
        var component = Qt.createComponent(panelObject.url)
        if (!component) {
            console.log("CAN'T CREATE: " + panelObject.url)
            return null
        }

        // Create panel
        var panel = component.createObject(panelMgr, {"panelObject": panelObject})
        if (!panel)
        {
            console.log("CREATEPANEL ERROR: " + component.errorString())
            return null
        }

        // Set target drone
        panel.targetDrone = targetDrone

        // Initialize panel
        panel.initialize()

        return panel
    }

    // Load specific panel
    function onLoadPanel(panelName)
    {
        // Finalize curret item
        if ((typeof currentItem !== "undefined") && (currentItem !== null))
            currentItem.finalize()

        var panelFound = false
        for (var i=0; i<depth; i++) {
            if (get(i, true).panelObject.name === panelName) {
                pop(get(i))
                panelFound = true
                break
            }
        }

        if (panelFound === false) {
            var panel = createPanel(panelName)
            if ((typeof panel !== "undefined") && (panel !== null))
            {
                panel.closePanel.connect(onClosePanel)
                push(panel)
            }
        }
    }

    // Close panel and load default payload panel
    function onClosePanel()
    {
        loadPanel("PayloadEditor")
    }

    Component.onCompleted: {
        panelMgr.loadPanel.connect(onLoadPanel)
        loadPanel("PayloadEditor")
    }
}
