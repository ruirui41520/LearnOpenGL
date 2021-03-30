#ifndef CUSTOMOPENGLWIDGET_H
#define CUSTOMOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include "customcamera.h"
#include "basemodel.h"
#include "cubemodel.h"
#include "planemodel.h"
#include "shader.h"
#include "windowmodel.h"
#include "skymodel.h"
#include "quadmodel.h"
#include <glm.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CustomOpenglWidget: public QOpenGLWidget,protected QOpenGLFunctions_3_3_Core
{
public:
    CustomOpenglWidget(QWidget *parent = nullptr);
    ~CustomOpenglWidget() Q_DECL_OVERRIDE;

    // QOpenGLWidget interface
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    void glError(QString content);

private:
    Shader *m_cubeshader, *m_sceenshader;
    bool m_leftPressed = false;
    QPoint m_lastPosition;
    std::unique_ptr<CustomCamera> m_camera;
    CubeModel *cube_model;
    QuadModel *screen_model;
    QTimer *m_timer;
    WindowModel* m_window;
    GLuint m_frameBuffer, m_textureColorbuffer, rbo, m_uboMatrices,m_textureColorBufferMultiSampled,m_screenFramebuffer,m_screenTexture;

    // QWidget interface
protected:

};

#endif // CUSTOMOPENGLWIDGET_H
