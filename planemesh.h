#pragma once
#include "basemesh.h"
#include <QImage>

class PlaneMesh:public BaseMesh
{
public:
    PlaneMesh();
    void initData(Shader *shader);
    void draw(Shader *shader);
private:
    GLuint m_textureId;

};
