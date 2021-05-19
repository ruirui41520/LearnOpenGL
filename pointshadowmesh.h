#pragma once
#include "basemesh.h"

class PointShadowMesh: public BaseMesh
{
public:
    PointShadowMesh();

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void draw(Shader *shader);
};
