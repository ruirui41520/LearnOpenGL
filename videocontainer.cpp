#include "videocontainer.h"
#include <QDebug>
#include <QCamera>
#include <QCameraViewfinder>
#include <QDateTime>


VideoContainer::VideoContainer(QObject *parent) : QObject(parent)
{
    m_probe = new QVideoProbe();
    m_surface = new CameraSurface();

}

VideoContainer::~VideoContainer()
{
    delete  m_probe;
    delete  m_surface;
}

void VideoContainer::load(){
    if (!m_qmlCamera || !m_provider) {
        qWarning() << "Invalid QML";
        return;
    }
    QCamera *p_camera = qvariant_cast<QCamera*>(m_qmlCamera->property("mediaObject"));
    assert(p_camera != nullptr);

    m_probe->setSource(p_camera);
    p_camera->setViewfinder(m_surface);
    m_provider->setFormat(1280, 720);
    QObject::connect(m_probe,&QVideoProbe::videoFrameProbed,m_provider,&RenderFrameProvider::onNewVideoContentReceived);

}

void VideoContainer::startCamera(bool autoLoad){
    QCamera *p_camera = qvariant_cast<QCamera*>(m_qmlCamera->property("mediaObject"));
    assert(p_camera != nullptr);
    p_camera->start();
    if(autoLoad){
        load();
    }
}

void VideoContainer::stopCamera(){
    QCamera *p_camera = qvariant_cast<QCamera*>(m_qmlCamera->property("mediaObject"));
    assert(p_camera != nullptr);
    p_camera->stop();
}



