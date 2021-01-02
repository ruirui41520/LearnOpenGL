#ifndef VIDEOCONTAINER_H
#define VIDEOCONTAINER_H
#include <QObject>
#include <QVideoProbe>
#include "camerasurface.h"
#include "dispatcher.h"
#include "renderframeprovider.h"
#include <QCameraImageCapture>

class VideoContainer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *qmlCamera READ qmlCamera WRITE setQmlCamera)
    Q_PROPERTY(RenderFrameProvider *provider READ frameProvider WRITE setFrameProvider)

public:
    explicit VideoContainer(QObject *parent = nullptr);
    ~VideoContainer();

public:
    void load();
    void startCamera(bool autoLoad = true);
    void stopCamera();

    QObject *qmlCamera() { return m_qmlCamera; }
    void setQmlCamera(QObject *camera) { m_qmlCamera = camera; };
    void processVideoFrame( QVideoFrame& frame );
    RenderFrameProvider *frameProvider() { return m_provider; }
    void setFrameProvider(RenderFrameProvider *provider) { m_provider = provider; };

private:
    QObject *m_qmlCamera;
    RenderFrameProvider *m_provider;
    QVideoProbe *m_probe;
    CameraSurface *m_surface;

};


#endif // VIDEOCONTAINER_H
