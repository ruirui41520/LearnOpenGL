#ifndef SHADOWMESH_H
#define SHADOWMESH_H
#include "basemesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShadowMesh:public BaseMesh
{
public:
    ShadowMesh();
    void draw(Shader *shader,QVector3D viewPos,int screenWidth,int screenHeight);

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void draw(Shader *shader){Q_UNUSED(shader)};

private:
    void drawShaderData(Shader *shader);

private:
    GLuint m_texture0Id, m_texture1Id;
    GLuint m_planeVAO,m_planeVBO,m_cubeVAO,m_cubeVBO;
    Shader* depthShader;
    GLuint depthMapFBO;
    GLint defaultFBO;
    const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
};

#endif // SHADOWMESH_H
