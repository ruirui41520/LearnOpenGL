#include "customopenglwidget.h"
#include <QDebug>
#include <QFile>
// path :terminal pwd
const QString path =
    "/Users/zhaodedong/Project/C++/OpenglDemo/nanosuit/nanosuit.obj";
CustomOpenglWidget::CustomOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
  m_camera = std::make_unique<CustomCamera>(QVector3D(5.0f, 0.0f, 10.0f));
  m_leftPressed = false;
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, [=] { update(); });
  m_timer->start(40);
  m_scene.reset(new PointShaderScene(m_camera.get(),this));
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  m_scene.get()->initializeGL();
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_camera->processInput(1.0f);
  //顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
  m_scene.get()->drawScene();
}

void CustomOpenglWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_leftPressed = true;
    m_lastPosition = event->pos();
  }
}

void CustomOpenglWidget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  m_leftPressed = false;
}

void CustomOpenglWidget::mouseMoveEvent(QMouseEvent *event) {
  if (m_leftPressed) {
    int xpos = event->pos().x();
    int ypos = event->pos().y();
    int xoffset = xpos - m_lastPosition.x();
    int yoffset = m_lastPosition.y() - ypos;
    m_lastPosition = event->pos();
    m_camera->processMouseMovement(xoffset, yoffset);
  }
}

void CustomOpenglWidget::wheelEvent(QWheelEvent *event) {
  QPoint point = event->angleDelta();
  m_camera->processMouseScroll(point.y() / 20.0f);
}

void CustomOpenglWidget::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key > 0 && key < 1024) {
    m_camera->keys[key] = true;
  }
}

void CustomOpenglWidget::keyReleaseEvent(QKeyEvent *event) {
  int key = event->key();
  if (key > 0 && key < 1024) {
    m_camera->keys[key] = false;
  }
}

void CustomOpenglWidget::glError(QString content) {
  if (GLenum err; (err = glGetError()) != GL_NO_ERROR) {
    qWarning() << "********" << content << "error :" << Qt::hex << err;
  }
}
