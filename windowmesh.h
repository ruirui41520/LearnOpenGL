#pragma once
#include "basemesh.h"
#include "customcamera.h"

class WindowMesh:public BaseMesh
{
public:
    WindowMesh();
    void initData(Shader *shader);
    void draw(Shader *shader);
private:
    GLuint m_textureId;
    std::map<float, QVector3D> sorted;
};

