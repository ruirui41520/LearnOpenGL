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
    BaseScene(CustomCamera* camera, QOpenGLWidget* widget);
    ~BaseScene();
    int screenWidth();
    int screenHeight();
    QMatrix4x4 getViewMat();
    QMatrix4x4 getProjection();
    QVector3D getViewPos();

public:
    virtual void initializeGL(){};
    virtual void drawScene(){};

public:
    std::unique_ptr<CustomCamera> m_camera;
    std::unique_ptr<QOpenGLWidget> m_widget;
};
