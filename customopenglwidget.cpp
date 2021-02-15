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
    plane_model = new PlaneModel();
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [=] { update(); });
    m_timer->start(40);
}

CustomOpenglWidget::~CustomOpenglWidget() {}

void CustomOpenglWidget::initializeGL() {
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    m_shader = new Shader(":/basic_lighting.vert", ":/basic_lighting.frag");
    m_colorShader = new Shader(":/stencil.vert", ":/stencil.frag");
    cube_model->bindData(m_shader);
    plane_model->bindData(m_shader);
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_camera->processInput(1.0f);
    //顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
    m_shader->bind();
    QMatrix4x4 m_projection;
    m_projection.perspective(m_camera->zoom, 1.0f * width() / height(), 0.1f,
                             100.0f);
    m_shader->setMat4("a_projection", m_projection);
    QMatrix4x4 m_view = m_camera->getViewMatrix();
    m_shader->setMat4("a_view", m_view);

    glStencilMask(0x00);
    plane_model->draw(m_shader);

    QMatrix4x4 m_model;
    m_model.translate(QVector3D(-1.0f, 0.0f, -1.0f));
    m_shader->setMat4("a_model", m_model);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    cube_model->draw(m_shader);
    m_model = QMatrix4x4();
    m_model.translate(QVector3D(2.0f, 0.0f, 0.0f));
    m_shader->setMat4("a_model", m_model);
    cube_model->draw(m_shader);
    m_shader->release();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    m_colorShader->bind();
    m_colorShader->setMat4("a_projection", m_projection);
    m_colorShader->setMat4("a_view", m_view);
    m_model = QMatrix4x4();
    m_model.translate(QVector3D(-1.0f, 0.0f, -1.0f));
    m_model.scale(QVector3D(1.1, 1.1, 1.1));
    m_colorShader->setMat4("a_model", m_model);
    cube_model->draw(m_colorShader);
    m_model = QMatrix4x4();
    m_model.translate(QVector3D(2.0f, 0.0f, 0.0f));
    m_model.scale(QVector3D(1.1, 1.1, 1.1));
    m_colorShader->setMat4("a_model", m_model);
    cube_model->draw(m_colorShader);
    m_colorShader->release();
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
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
