#pragma once
#include "basemesh.h"

class PointShadowDepthMesh:public BaseMesh
{
public:
    PointShadowDepthMesh();

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void draw(Shader *shader);
};
