#pragma once
#include "basemesh.h"
#include <QImage>

class CubeMesh: public BaseMesh
{
public:
    CubeMesh();
    // BaseMesh interface
    void initData(Shader *shader);
    void draw(Shader *shader=nullptr);

private:
    GLuint m_textureId, m_uboMatrices;
};

