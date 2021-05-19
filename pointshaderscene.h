#pragma once
#include "basescene.h"
#include "customcamera.h"
#include "basemodel.h"
#include "pointshadowmodel.h"
#include "pointshadowdepthmodel.h"
#include "shader.h"
class PointShaderScene:public BaseScene
{
public:
    PointShaderScene(CustomCamera* camera, QOpenGLWidget* widget);
    // BaseScene interface
public:
    void initializeGL();
    void drawScene();

    // BaseScene interface
private:
    void bindCommonData();

public:
    GLuint SHADOW_VAO = 0, SHADOW_VBO = 0, SHADOW_WIDTH = 2048,SHADOW_HEIGHT = 2048;
    QVector3D lightPos = QVector3D(0.0f, 0.0f, 0.0f);
    Shader *m_pointShadowShader,*m_pointShadowDepthShader;
    PointShadowModel *m_pointShadowModel;
    PointShadowDepthModel *m_pointShadowDepthModel;
    GLuint m_uboMatrices, depthCubemap, depthMapFBO;

};
