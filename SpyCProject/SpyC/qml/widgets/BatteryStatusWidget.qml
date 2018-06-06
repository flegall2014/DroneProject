import QtQuick 2.5
import QtGraphicalEffects 1.0
import Components 1.0
import ".."

Column {
    id: root
    property int batteryLevel: 0
    property int returnLevel: 0

    spacing: Theme.standardSpacing/2
    BatteryWidget {
        id: batWidget1
        currentLevel: root.batteryLevel
        batteryColor: "green"
    }
    BatteryWidget {
        id: batWidget2
        currentLevel: root.returnLevel
        batteryColor: "orange"
    }
}
