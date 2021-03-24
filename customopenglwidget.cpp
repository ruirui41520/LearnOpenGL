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
  cube_model = new CubeModel();
  sky_model = new SkyModel();
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, [=] { update(); });
  m_timer->start(40);
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  m_skyshader = new Shader(":/sky.vert", ":/sky.frag");
  m_cubeshader = new Shader(":/cube.vert", ":/cube.frag");
  cube_model->bindData(m_cubeshader);
  sky_model->bindData(m_skyshader);

  GLuint m_uniformBlockCube = glGetUniformBlockIndex(m_cubeshader->shaderId(), "Matrices");
  GLuint m_uniformBlockSky = glGetUniformBlockIndex(m_skyshader->shaderId(), "Matrices");
  glUniformBlockBinding(m_cubeshader->shaderId(),m_uniformBlockCube,0);
  glUniformBlockBinding(m_skyshader->shaderId(),m_uniformBlockSky,0);
  glGenBuffers(1,&m_uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER,m_uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER,32*sizeof (float),NULL,GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER,0);
  glBindBufferRange(GL_UNIFORM_BUFFER,0, m_uboMatrices,0 , 32*sizeof (float));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  m_camera->processInput(1.0f);
  //顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
  QMatrix4x4 m_projection;
  m_projection.perspective(m_camera->zoom, 1.0f * width() / height(), 0.1f,
                           100.0f);
  QMatrix4x4 m_view = m_camera->getViewMatrix();
  glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER,0, 16*sizeof (float), m_projection.data());
  glBufferSubData(GL_UNIFORM_BUFFER, 16*sizeof (float),16*sizeof (float), m_view.data());
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  m_cubeshader->bind();
  QMatrix4x4 m_model = QMatrix4x4();
  m_model.translate(QVector3D(2.0f, 0.0f, 0.0f));
  m_cubeshader->setMat4("a_model", m_model);
  cube_model->draw(m_cubeshader);
  m_model.translate(-4.0f, 2.0f, 0.0f);
  m_cubeshader->setMat4("a_model", m_model);
  cube_model->draw(m_cubeshader);

  glDepthFunc(GL_LEQUAL);
  m_skyshader->bind();
  sky_model->draw(m_skyshader);
  m_skyshader->release();
  m_cubeshader->release();
  glDepthFunc(GL_LESS);
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
