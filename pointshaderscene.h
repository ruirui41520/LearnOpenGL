#pragma once
#include "basescene.h"
#include "customcamera.h"
#include "basemodel.h"
#include "pointshadowmodel.h"
#include "pointshadowdepthmodel.h"
#include "shader.h"
#include "res.h"
class PointShaderScene:public BaseScene
{
public:
    PointShaderScene(CustomCamera* camera, QOpenGLWidget* widget);
    // BaseScene interface
public:
    void initializeGL();
    void drawScene();

private:
    void bindCommonData();

public:
    GLuint SHADOW_VAO = 0, SHADOW_VBO = 0;
    QVector3D lightPos = QVector3D(0.0f, 0.0f, 0.0f);
    Shader *m_pointShadowShader,*m_pointShadowDepthShader;
    PointShadowModel *m_pointShadowModel;
    PointShadowDepthModel *m_pointShadowDepthModel;
    GLuint m_uboMatrices, depthCubemap, depthMapFBO;
    GLint defaultFrameFBO;

};
