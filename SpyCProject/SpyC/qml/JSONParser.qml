import QtQuick 2.5

Item {
    property string source
    signal dataReady(string responseText)

    function request(source) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function()
        {
            if (xhr.readyState === XMLHttpRequest.DONE)
                dataReady(xhr.responseText)
        }
        xhr.open("GET", source, true)
        xhr.send("")
    }

    // Source changed:
    onSourceChanged: request(source)
}
