#pragma once
#include "basemesh.h"
#include "res.h"

class PointShadowMesh: public BaseMesh
{
public:
    PointShadowMesh();

private:
    void drawCube(Shader *shader);

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void drawWithVariab(Shader *shader, QVector3D eyePos, GLuint cubeId);

public:
    GLuint woodTextureId;
};
