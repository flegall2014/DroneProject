import QtQuick 2.5
import Components 1.0
import ".."

ListView {
    id: listView
    clip: true
    property variant columnTitles: [
        "Index",
        "Latitude",
        "Longitude",
        "Altitude",
        "Ground height",
        "Point speed"
    ]
    header: Component {
        id: headerComponent
        Row {
            width: listView.width
            height: Theme.standardDelegateHeight
            Repeater {
                model: columnTitles
                Item {
                    width: parent.width/columnTitles.length
                    height: parent.height
                    StandardText {
                        anchors.centerIn: parent
                        text: columnTitles[index]
                    }
                }
            }
        }
    }
    delegate: Item {
        width: listView.width
        height: Theme.standardDelegateHeight

        Row {
            anchors.fill: parent

            // Index delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointIndex
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
                onItemClicked: listView.model.currentPointIndex = index
            }

            // Latitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLatitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
                onItemClicked: listView.model.currentPointIndex = index
            }

            // Longitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointLongitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
                onItemClicked: listView.model.currentPointIndex = index
            }

            // Altitude delegate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: wayPointAltitude.toFixed(3)
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
                onItemClicked: listView.model.currentPointIndex = index
            }

            // Ground height deleagate
            WayPointDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                text: "0"
                color: index === listView.model.currentPointIndex ? Theme.selectedColor : Theme.defaultFontColor
                onItemClicked: listView.model.currentPointIndex = index
            }

            // Speed delegate
            SpeedDelegate {
                width: listView.width/columnTitles.length
                height: parent.height
                echoRadioChecked: wayPointSpeed === WayPointModel.ECO
                obsRadioChecked: wayPointSpeed === WayPointModel.OBS
                fastRadioChecked: wayPointSpeed === WayPointModel.FAST
                onEcoClicked: {
                    wayPointSpeed = WayPointModel.ECO
                    listView.model.currentPointIndex = index
                }
                onObsClicked: {
                    wayPointSpeed = WayPointModel.OBS
                    listView.model.currentPointIndex = index
                }
                onFastClicked: {
                    wayPointSpeed = WayPointModel.FAST
                    listView.model.currentPointIndex = index
                }
            }
        }

        // Top separator
        Rectangle {
            anchors.top: parent.top
            width: parent.width
            height: 1
            color: "green"
        }

        // Bottom separator
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: "green"
            visible: index === listView.model.pointCount-1
        }
    }
}
