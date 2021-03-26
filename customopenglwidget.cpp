#include "customopenglwidget.h"
#include <QDebug>
#include <QFile>
// path :terminal pwd
const QString planet_path = "/Users/cl10077-tmp/LearnOpenGL/planet/planet.obj";
const QString rock_path = "/Users/cl10077-tmp/LearnOpenGL/rock/rock.obj";
CustomOpenglWidget::CustomOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
  m_camera = std::make_unique<CustomCamera>(QVector3D(5.0f, 0.0f, 10.0f));
  m_leftPressed = false;
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, &CustomOpenglWidget::slotTimeout);
  m_timer->start(40);
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  planet_model = new Model(planet_path);
  rock_model = new InstanceModel(rock_path);
  planet_shader = new Shader(":/planet.vert", ":/planet.frag", ":/planet.gs");
  rock_shader = new Shader(":/rock.vert", ":/rock.frag");
  GLuint m_uniformBlockPlanet =
      glGetUniformBlockIndex(planet_shader->programId(), "Matrices");
  GLuint m_uniformBlockRock =
      glGetUniformBlockIndex(rock_shader->programId(), "Matrices");
  glUniformBlockBinding(planet_shader->programId(), m_uniformBlockPlanet, 0);
  glUniformBlockBinding(rock_shader->programId(), m_uniformBlockRock, 0);
  glGenBuffers(1, &m_uniformBuffer);
  glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
  glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uniformBuffer, 0,
                    2 * sizeof(glm::mat4));
  glEnable(GL_DEPTH_TEST);
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_camera->processInput(1.0f);
  QMatrix4x4 m_projection;
  m_projection.perspective(m_camera->zoom, 1.0f * width() / height(), 10.0f,
                           1000.0f);
  QMatrix4x4 m_view = m_camera->getViewMatrix();
  QMatrix4x4 m_model;
  m_model.translate(QVector3D(0.0f, -15.0f, -50.0f));
  glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
  glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof (glm::mat4),m_projection.data());
  glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4), sizeof(glm::mat4),m_view.data());
  glBindBuffer(GL_UNIFORM_BUFFER,0);
  //    顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
  planet_shader->bind();
  planet_shader->setMat4("a_model", m_model);
  planet_shader->setFloat("time", 0);
  planet_model->draw(planet_shader);
  planet_shader->release();

  rock_shader->bind();
  rock_model->draw(rock_shader);
  rock_shader->release();
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

void CustomOpenglWidget::slotTimeout() {
  m_nTimeValue += 5;
  update();
}

void CustomOpenglWidget::glError(QString content) {
  if (GLenum err; (err = glGetError()) != GL_NO_ERROR) {
    qWarning() << "********" << content << "error :" << Qt::hex << err;
  }
}
