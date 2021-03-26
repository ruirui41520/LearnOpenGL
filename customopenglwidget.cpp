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
  quad_model = new QuadModel();
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, [=] { update(); });
  m_timer->start(40);
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  m_cubeshader = new Shader(":/cube.vert", ":/cube.frag");
  m_quadshader = new Shader(":/quad.vert",":/quad.frag");
  cube_model->bindData(m_cubeshader);
  quad_model->bindData(m_quadshader);

  GLuint m_uniformBlockCube = glGetUniformBlockIndex(m_cubeshader->shaderId(), "Matrices");
  glUniformBlockBinding(m_cubeshader->shaderId(),m_uniformBlockCube,0);
  glGenBuffers(1,&m_uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER,m_uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER,32*sizeof (float),NULL,GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER,0);
  glBindBufferRange(GL_UNIFORM_BUFFER,0, m_uboMatrices,0 , 32*sizeof (float));

  glGenFramebuffers(1,&m_frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
  glGenTextures(1,&m_textureColorBufferMultiSampled);
  glBindTexture(GL_PROXY_TEXTURE_2D_MULTISAMPLE,m_textureColorBufferMultiSampled);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,width(),height(),GL_TRUE);
  glBindTexture(GL_PROXY_TEXTURE_2D_MULTISAMPLE,0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,m_textureColorBufferMultiSampled,0);
  glGenRenderbuffers(1,&rbo);
  glBindRenderbuffer(GL_RENDERBUFFER,rbo);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,width(),height());
  glBindRenderbuffer(GL_RENDERBUFFER,0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glGenFramebuffers(1,&m_screenFramebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER,m_screenFramebuffer);
  glGenTextures(1,&m_screenTexture);
  glBindTexture(GL_TEXTURE_2D,m_screenTexture);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width(),height(),0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_screenTexture,0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

  glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  m_cubeshader->bind();
  QMatrix4x4 m_model = QMatrix4x4();
  m_model.translate(QVector3D(2.0f, 0.0f, 0.0f));
  m_cubeshader->setMat4("a_model", m_model);
  cube_model->draw(m_cubeshader);
  m_model.translate(-4.0f, 2.0f, 0.0f);
  m_cubeshader->setMat4("a_model", m_model);
  cube_model->draw(m_cubeshader);
  m_cubeshader->release();

  glBindFramebuffer(GL_READ_FRAMEBUFFER,m_frameBuffer);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,m_screenFramebuffer);
  glBlitFramebuffer(0,0,width(),height(),0,0,width(),height(),GL_COLOR_BUFFER_BIT,GL_NEAREST);

  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  m_quadshader->bind();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_screenTexture);
  quad_model->draw(m_quadshader);
  m_quadshader->release();

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
