#include "customopenglwidget.h"
#include "renderframeprovider.h"
#include "shadertransferutil.h"
#include "videocontainer.h"
#include <QApplication>
#include <QCoreApplication>
#include <QImage>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickView>
#include <QtMultimedia>

QQuickView *m_mainWindow;
CustomOpenglWidget *widget;
void startCamera() {
  QQuickItem *rootObject = m_mainWindow->rootObject();
  VideoContainer *container =
      rootObject->findChild<VideoContainer *>("videoContainer");
  assert(container != nullptr);
  container->startCamera();
}

void registerQMLType() {
  qmlRegisterType<VideoContainer>("OpenglDemo", 1, 0, "VideoContainer");
  qmlRegisterType<RenderFrameProvider>("OpenglDemo", 1, 0,
                                       "RenderFrameProvider");
}

void showWindow(QApplication &app) {
  m_mainWindow->setResizeMode(QQuickView::SizeRootObjectToView);
  QObject::connect(m_mainWindow, SIGNAL(destroyed()), &app, SLOT(quit()));
  QObject::connect(m_mainWindow->engine(), &QQmlEngine::quit, qApp,
                   &QApplication::quit);
  m_mainWindow->setSource(QUrl("qrc:/main.qml"));
  m_mainWindow->resize(890, 652);
  m_mainWindow->setMinimumWidth(650);
  m_mainWindow->setMinimumHeight(652);
  m_mainWindow->setTitle("OpenglDemo test");
  m_mainWindow->show();
  startCamera();
}

void initGLSurface() {
  QSurfaceFormat glFormat;
  glFormat.setVersion(3, 3);
  glFormat.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(glFormat);
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  registerQMLType();
  initGLSurface();
  m_mainWindow = new QQuickView;
//  showWindow(app);
  widget = new CustomOpenglWidget();
  widget->setWindowTitle(QObject::tr("CustomGLWidget"));
  widget->show();
  return app.exec();
}
