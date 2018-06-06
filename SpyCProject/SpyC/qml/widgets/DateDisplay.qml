import QtQuick 2.5

StandardText {
    id: dateTime
    property string dateTimeString: "Tue 2013-09-17 10:56:06"
    verticalAlignment: Text.AlignVCenter
    function updateText()
    {
        dateTime.text = Date().toString()
    }
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: dateTime.updateText()
    }
}
