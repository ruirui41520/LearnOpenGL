#pragma once
#include "basemesh.h"

class QuadMesh:public BaseMesh
{
public:
    QuadMesh();
public:
    void initData(Shader *shader);
    void draw(Shader *shader);
};
