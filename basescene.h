#pragma once
#include "shader.h"
#include "customcamera.h"
#include <QVector>
#include <QVector3D>
#include <QImage>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <QOpenGLWidget>
class BaseScene
{
public:
    BaseScene(CustomCamera* camera, QOpenGLWidget* widget){
        m_camera.reset(camera);
        m_widget.reset(widget);
    };
    virtual void initializeGL();
    virtual void drawScene();
    int screenWidth(){return m_widget.get()->width();};
    int screenHeight(){return m_widget.get()->height();};
    QMatrix4x4 getViewMat(){return m_camera.get()->getViewMatrix();};
    QMatrix4x4 getProjection(){
        QMatrix4x4 m_projection;
        m_projection.perspective(m_camera->zoom, 1.0f * screenWidth() / screenHeight(), 0.1f,
                                 1000.0f);
        return m_projection;
    };

private:
    virtual void bindCommonData();

public:
    std::unique_ptr<CustomCamera> m_camera;
    std::unique_ptr<QOpenGLWidget> m_widget;
};
