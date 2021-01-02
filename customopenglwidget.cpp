#include "customopenglwidget.h"
#include <QDebug>
#include <QFile>

static QVector3D lightPos(1.2f, 1.0f, 2.0f);
CustomOpenglWidget::CustomOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
    m_camera = std::make_unique<CustomCamera>(QVector3D(5.0f, 0.0f, 10.0f));
    m_leftPressed = false;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [=] {
        m_rotate += 1;
        update();
    });
    m_timer->start(50);
}

CustomOpenglWidget::~CustomOpenglWidget() {
    glDeleteBuffers(1, &m_element_buffer_obj);
    glDeleteBuffers(1, &m_vertex_buffer_obj);
    glDeleteVertexArrays(1, &m_vertex_cube_obj);
    glDeleteVertexArrays(1,&m_vertex_lamp_obj);
}

void CustomOpenglWidget::initializeGL() {
    this->initializeOpenGLFunctions();
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

    bool success = m_colorProgram.addCacheableShaderFromSourceFile(
                QOpenGLShader::Vertex, ":/basic_lighting.vert");
    if (!success) {
        glError("addCacheableShaderFromSourceVertex");
        return;
    }
    success = m_colorProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
                                                         ":/basic_lighting.frag");
    if (!success) {
        glError("addCacheableShaderFromSourceFragment");
        return;
    }
    m_colorProgram.link();

    success = m_lampProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/lamp.vert");
    if (!success) {
        glError("addCacheableShaderFromSourceFile");
        return;
    }
    success = m_lampProgram.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/lamp.frag");
    if(!success){
        glError("addCacheableShaderFromSourceFragment");
        return;
    }
    m_lampProgram.link();

    glGenVertexArrays(1, &m_vertex_cube_obj);
    glGenVertexArrays(1, &m_vertex_lamp_obj);
    glGenBuffers(1, &m_vertex_buffer_obj);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_obj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    {
        glBindVertexArray(m_vertex_cube_obj);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof (GL_FLOAT),(void*)(3*sizeof (GL_FLOAT)));
        glEnableVertexAttribArray(1);
    }
    {
        glBindVertexArray(m_vertex_lamp_obj);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof (GL_FLOAT),(void*)0);
        glEnableVertexAttribArray(0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

void CustomOpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void CustomOpenglWidget::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_camera->processInput(1.0f);
    //顺序：缩/转/移 -》 matrix_translate * matrix_rotate * matrix_scale
    m_colorProgram.bind();
    QMatrix4x4 m_projection;
    m_projection.perspective(m_camera->zoom,1.0f *width() / height(),0.1f,100.0f);
    m_colorProgram.setUniformValue("a_projection",m_projection);
    QMatrix4x4 m_view = m_camera->getViewMatrix();
    m_colorProgram.setUniformValue("a_view",m_view);
    QMatrix4x4 m_model;
    m_colorProgram.setUniformValue("a_model",m_model);
    m_colorProgram.setUniformValue("lampColor",QVector3D(1.0f, 0.5f, 0.31f));
    m_colorProgram.setUniformValue("objColor",QVector3D(1.0f, 1.0f, 1.0f));
    m_colorProgram.setUniformValue("viewPosition",QVector3D(0.0f,0.0f,3.0f));
    m_colorProgram.setUniformValue("lightPosition",lightPos);
    {
        glBindVertexArray(m_vertex_cube_obj);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
    m_colorProgram.release();

    m_lampProgram.bind();
    m_lampProgram.setUniformValue("a_projection",m_projection);
    m_lampProgram.setUniformValue("a_view",m_view);
    m_model = QMatrix4x4();
    m_model.translate(lightPos);
    m_model.scale(0.2f);
    m_lampProgram.setUniformValue("a_model",m_model);
    {
        glBindVertexArray(m_vertex_lamp_obj);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
    m_lampProgram.release();

}

void CustomOpenglWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_leftPressed = true;
        m_lastPosition = event->pos();
    }
}

void CustomOpenglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_leftPressed = false;
}

void CustomOpenglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_leftPressed){
        int xpos = event->pos().x();
        int ypos = event->pos().y();
        int xoffset = xpos - m_lastPosition.x();
        int yoffset = m_lastPosition.y() - ypos;
        m_lastPosition = event->pos();
        m_camera->processMouseMovement(xoffset , yoffset);
    }
}

void CustomOpenglWidget::wheelEvent(QWheelEvent *event)
{
    QPoint point = event->angleDelta();
    m_camera->processMouseScroll(point.y() / 20.0f);
}

void CustomOpenglWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key >0 && key < 1024){
        m_camera->keys[key] = true;
    }
}

void CustomOpenglWidget::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key > 0 && key < 1024){
        m_camera->keys[key] = false;
    }
}

void CustomOpenglWidget::glError(QString content) {
    if (GLenum err; (err = glGetError()) != GL_NO_ERROR) {
        qWarning() << "********" << content << "error :" << Qt::hex << err;
    }
}
