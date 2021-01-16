import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia 5.4
import OpenglDemo 1.0


Item {
    id: root
    width: 640
    height: 420
    visible: true

    Loader{
        id:cameraLoader
        sourceComponent: QtMultimedia.availableCameras.length <= 0 ? cameraComponent : undefined
    }

    Component{
        id:cameraComponent
        CameraCaptureContainer{
            id:cameraContainer
            theID: "dfadfa"
        }
    }

}
