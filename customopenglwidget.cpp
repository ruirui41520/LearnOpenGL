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
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  m_planeshader = new Shader(":/plane.vert", ":/plane.frag");
  m_planeModel = new PlaneModel();
  m_planeModel->bindData(m_planeshader);

  GLuint m_uniformBlockCube =
      glGetUniformBlockIndex(m_planeshader->shaderId(), "Matrices");
  glUniformBlockBinding(m_planeshader->shaderId(), m_uniformBlockCube, 0);
  glGenBuffers(1, &m_uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uboMatrices, 0,
                    2 * sizeof(glm::mat4));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_camera->processInput(1.0f);
  //顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
  QMatrix4x4 m_projection;
  m_projection.perspective(m_camera->zoom, 1.0f * width() / height(), 0.1f,
                           1000.0f);
  QMatrix4x4 m_view = m_camera->getViewMatrix();
  glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), m_view.data());
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4),
                  m_projection.data());
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  QVector3D lightPos(3.0f, 3.0f, 0.0f);
  QVector3D viewPos = m_camera->getPosition();
  m_planeshader->bind();
  m_planeshader->setVec3("viewPos", viewPos);
  m_planeshader->setVec3("lightPos",lightPos);
  m_planeshader->setInt("blinn",blinn);
  m_planeModel->draw(m_planeshader);
  m_planeshader->release();
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
