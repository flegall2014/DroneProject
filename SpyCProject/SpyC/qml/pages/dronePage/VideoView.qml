import QtQuick 2.0
import QtMultimedia 5.2
import Components 1.0
import "../../widgets"
import "../.."

// Video area
Rectangle {
    id: videoArea
    color: Theme.videoBkgColor
    property variant targetDrone
    signal maximizeVideo()

    // Play video
    function play()
    {
        video.play()
    }

    // Stop video
    function stop()
    {
        video.stop()
    }

    // Take snapshot
    function takeSnapShot()
    {
        video.grabToImage(function(image) {
            var snapShotPath = targetDrone.galleryModel.getNextSnapShotName(targetDrone.uid)
            image.saveToFile(snapShotPath)
            targetDrone.galleryModel.addSnapShot(snapShotPath, targetDrone.position)
        });
    }

    // Video
    Video {
        id: video
        anchors.fill: parent
        source: HELPER.fromLocalFile(targetDrone.videoUrl)
        onSourceChanged: console.log("******************************** ", source)
        loops: MediaPlayer.Infinite
        focus: true
        opacity: targetDrone.flightStatus === SpyC.FLYING ? 1 : 0
        visible: opacity > 0
        autoPlay: true
        autoLoad: true
        Behavior on opacity {
            NumberAnimation {duration: Theme.standardAnimationDuration}
        }
        onVisibleChanged: {
            if (visible)
                play()
            else
                stop()
        }
    }

    // No video image
    Item {
        id: noVideoImage
        anchors.fill: parent
        opacity: targetDrone.flightStatus !== SpyC.FLYING ? 1 : 0
        visible: opacity > 0
        Behavior on opacity {
            NumberAnimation {duration: Theme.standardAnimationDuration}
        }
        Image {
            anchors.centerIn: parent
            source: "qrc:/images/img-novideo.jpg"
        }
    }

    // Display current lat/lon
    StandardText {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.standardMargin
        anchors.right: parent.right
        anchors.rightMargin: Theme.standardMargin
        text: targetDrone.position.latitude.toFixed(2) + " / " + targetDrone.position.longitude.toFixed(2)
        font.pixelSize: Theme.largeFontSize
        font.bold: true
    }
}
