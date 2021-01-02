import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia 5.4
import OpenglDemo 1.0


Item {
    id: root
    width: 640
    height: 420
    visible: true

    Camera {
        id:camera
        objectName: "camera"
        captureMode: Camera.CaptureVideo
        viewfinder {
            resolution: Qt.size(1280 ,720 )
        }
    }

    RenderFrameProvider {
        objectName: "provider"
        id: provider
    }

    VideoOutput {
        id:viewfinder
        objectName: "videoOutput"
        x: 10
        y: 15
        width: 500
        height: 400
        source: provider
        autoOrientation: true
        fillMode: VideoOutput.PreserveAspectCrop
    }

    VideoContainer {
        id: container
        objectName: "videoContainer"
        provider: provider
        qmlCamera: camera
    }

}
