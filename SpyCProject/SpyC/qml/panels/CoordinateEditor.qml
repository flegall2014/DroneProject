import QtQuick 2.5
import QtLocation 5.3
import QtQuick.Controls 1.4
import "../widgets"
import ".."

Row {
    property variant coordinate
    signal latitudeChanged(double latitude)
    signal longitudeChanged(double longitude)
    signal altitudeChanged(double altitude)
    height: Theme.standardDelegateHeight

    StandardLabelTextField {
        label: qsTr("Latitude")
        text: coordinate.latitude.toFixed(3)
        onValueChanged: latitudeChanged(value)
    }

    StandardLabelTextField {
        label: qsTr("Longitude")
        text: coordinate.longitude.toFixed(3)
        onValueChanged: longitudeChanged(value)
    }

    StandardLabelTextField {
        label: qsTr("Altitude")
        text: coordinate.altitude.toFixed(3)
        onValueChanged: altitudeChanged(value)
    }
}
