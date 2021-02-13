#include "customopenglwidget.h"
#include <QDebug>
#include <QFile>

static QVector3D lightPos(1.2f, 1.0f, 2.0f);
static QVector3D cubePositions[] = {
     QVector3D( 0.0f,  0.0f,  0.0f),
     QVector3D( 2.0f,  5.0f, -15.0f),
     QVector3D(-1.5f, -2.2f, -2.5f),
     QVector3D(-3.8f, -2.0f, -12.3f),
     QVector3D( 2.4f, -0.4f, -3.5f),
     QVector3D(-1.7f,  3.0f, -7.5f),
     QVector3D( 1.3f, -2.0f, -2.5f),
     QVector3D( 1.5f,  2.0f, -2.5f),
     QVector3D( 1.5f,  0.2f, -1.5f),
     QVector3D(-1.3f,  1.0f, -1.5f)
};

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
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof (GL_FLOAT),(void*)(3*sizeof (GL_FLOAT)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(2);
    }
    {
        glBindVertexArray(m_vertex_lamp_obj);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof (GL_FLOAT),(void*)0);
        glEnableVertexAttribArray(0);
    }
    glGenTextures(1,&m_texture1);
    glBindTexture(GL_TEXTURE_2D,m_texture1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    QImage diffuseMap = QImage(":/container2.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true,true);
    if(!diffuseMap.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,diffuseMap.width(),diffuseMap.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,diffuseMap.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glGenTextures(1,&m_texture2);
    glBindTexture(GL_TEXTURE_2D,m_texture2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    QImage specularMap = QImage(":/container2_specular.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true,true);
    if(!specularMap.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,specularMap.width(),specularMap.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,specularMap.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D,0);
    m_colorProgram.bind();
    glUniform1i(m_colorProgram.uniformLocation("mateliar.diffuse"),0);
    glUniform1i(m_colorProgram.uniformLocation("mateliar.specular"),1);
    m_colorProgram.release();

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
    m_colorProgram.setUniformValue("a_view", m_view);
    m_colorProgram.setUniformValue("lampColor",QVector3D(1.0f, 0.5f, 0.31f));
    m_colorProgram.setUniformValue("objColor",QVector3D(1.0f, 1.0f, 1.0f));
    m_colorProgram.setUniformValue("viewPosition",QVector3D(0.0f,0.0f,3.0f));
    m_colorProgram.setUniformValue("light.direction",QVector3D(-0.2f, -1.0f, -0.3f));
    m_colorProgram.setUniformValue("mateliar.shininess", 64.0f);
    m_colorProgram.setUniformValue("light.position", lightPos);
    m_colorProgram.setUniformValue("light.ambient", QVector3D(0.2f, 0.2f, 0.2f));
    m_colorProgram.setUniformValue("light.diffuse", QVector3D(0.5f, 0.5f, 0.5f));
    m_colorProgram.setUniformValue("light.specular", QVector3D(1.0f, 1.0f, 1.0f));
    m_colorProgram.setUniformValue("light.constant", 1.0f);
    m_colorProgram.setUniformValue("light.linear", 0.09f);
    m_colorProgram.setUniformValue("light.quadratic", 0.032f);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,m_texture2);
    //    m_colorProgram.set
    QMatrix4x4 m_model;
    {
        glBindVertexArray(m_vertex_cube_obj);
        for (unsigned int i = 0; i < 10;i++ ) {
            m_model.translate(cubePositions[i]);
            float rotation = (i + 1.0f) * m_rotate;
            m_model.rotate(rotation,QVector3D(1.0f, 0.3f, 0.5f));
            m_colorProgram.setUniformValue("a_model",m_model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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
