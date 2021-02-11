#ifndef CUSTOMOPENGLWIDGET_H
#define CUSTOMOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QTimer>
#include "customcamera.h"
#include "model.h"


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

private slots:
    void slotTimeout();

private:
    void glError(QString content);

private:
    QOpenGLShaderProgram m_Program;
    QTimer *m_timer;
    bool m_leftPressed = false;
    QPoint m_lastPosition;
    std::unique_ptr<CustomCamera> m_camera;
    Model* local_model;
    // QWidget interface
protected:

};

#endif // CUSTOMOPENGLWIDGET_H
