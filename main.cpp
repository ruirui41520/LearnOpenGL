#include <QApplication>
#include <QCoreApplication>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QtMultimedia>
#include "videocontainer.h"
#include "renderframeprovider.h"
#include "customopenglwidget.h"
#include "shadertransferutil.h"
#include <QImage>

QQuickView *m_mainWindow;

void startCamera()
{
    QQuickItem *rootObject = m_mainWindow->rootObject();
    VideoContainer *container = rootObject->findChild<VideoContainer*>("videoContainer");
    assert(container != nullptr);
    container->startCamera();
}

void registerQMLType(){
    qmlRegisterType<VideoContainer>("OpenglDemo", 1, 0, "VideoContainer");
    qmlRegisterType<RenderFrameProvider>("OpenglDemo", 1, 0, "RenderFrameProvider");
}


int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
//    registerQMLType();
//    m_mainWindow = new QQuickView;
//    m_mainWindow->setResizeMode(QQuickView::SizeRootObjectToView);
//    QObject::connect(m_mainWindow, SIGNAL( destroyed() ), &app, SLOT( quit() ));
//    QObject::connect(m_mainWindow->engine(), &QQmlEngine::quit,
//                     qApp, &QApplication::quit);

//    m_mainWindow->setSource(QUrl("qrc:/main.qml"));
//    m_mainWindow->resize(890, 652);
//    m_mainWindow->setMinimumWidth(650);
//    m_mainWindow->setMinimumHeight(652);
//    m_mainWindow->setTitle("OpenglDemo test");
//    m_mainWindow->show();
//    startCamera();

    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);
    CustomOpenglWidget widget;
    widget.setWindowTitle(QObject::tr("CustomGLWidget"));
    widget.show();

    return app.exec();
}


