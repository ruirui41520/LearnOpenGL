#ifndef SKYMESH_H
#define SKYMESH_H
#include "basemesh.h"

class SkyMesh:public BaseMesh
{
public:
    SkyMesh();

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void draw(Shader *shader);
private:
    GLuint loadTexture(QVector<QString>);

private:
    GLuint m_textureId;
};

#endif // SKYMESH_H
