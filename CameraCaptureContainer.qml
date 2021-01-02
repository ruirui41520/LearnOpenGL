import QtQuick 2.0

Item {
    id:root
    signal captureImage;
    signal saveImage;
    signal hidePage;
    property string source
    width: 125
    height: 150


//    function refreshImage(){
//        source = ""
//        source = "image://myprovider/default.png"
//    }

    states: [
        State {
            when: push
            PropertyChanges { target: root; x: 0; opacity: 1 }
        },
        State {
            when: !push
            PropertyChanges { target: root; x: width; opacity: 0.2 }
        }
    ]

    Rectangle{
        color: "black"
        anchors.fill: parent

        Component{
            id: capturePanelContainer
            Rectangle{
                width: 120
                border.width: 2
                border.color: "white"
                radius: 3
                color: "transparent"
                anchors{
                    top: parent.top
                }

                Image {
                    id: closePanel
                    width: 30
                    height: 20
                    source: "qrc:wall.jpg"
                    anchors{
                        top:parent.top
                        topMargin: 10
                        horizontalCenter: parent.horizontalCenter
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {

                        }
                    }
                }

                Image {
                    id: displayView
                    width: 110
                    height: 60
                    source: root.source
                    anchors{
                        top: closePanel.bottom
                        topMargin: 10
                        horizontalCenter: parent.horizontalCenter
                    }
                }

                Rectangle{
                    id:captureLoadContainer
                    width: 120
                    height: 40
                    color: "transparent"
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 5
                    }

                    Rectangle{
                        id:captureIconContent
                        width: 60
                        color: "transparent"
                        height: parent.height
                        anchors{
                            left: parent.left
                        }

                        Image {
                            id: imageCaptureIcon
                            width: 20
                            height: 20
                            anchors{
                                left: parent.left
                                leftMargin: 5
                                verticalCenter: parent.verticalCenter
                            }
                            source: "qrc:wall.jpg"
                        }

                        Text {
                            id: captureTitle
                            text: qsTr("Capture")
                            anchors{
                                left: imageCaptureIcon.right
                                verticalCenter: parent.verticalCenter
                            }
                            color: "white"
                            font{
                                pixelSize: 12
                                bold: true
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: captureImage();
                        }
                    }
                    Rectangle{
                        id:saveIconContent
                        width: 60
                        color: "transparent"
                        height: parent.height
                        anchors{
                            right: parent.right
                            left: captureIconContent.right
                        }

                        Text {
                            id: loadTitle
                            text: qsTr("Save")
                            anchors{
                                right: parent.right
                                rightMargin: 5
                                verticalCenter: parent.verticalCenter
                            }
                            color: "white"
                            font{
                                pixelSize: 12
                                bold: true
                            }
                        }

                        Image {
                            id: imageSaveIcon
                            width: 20
                            height: 20
                            source: "qrc:test.jpeg"
                            anchors{
                                right: loadTitle.left
                                verticalCenter: parent.verticalCenter
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: saveImage();
                        }
                    }

                }
            }
        }
    }
}
