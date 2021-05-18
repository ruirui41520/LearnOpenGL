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
    void draw(Shader *shader,QVector3D viewPos);

    // BaseMesh interface
public:
    void initData(Shader *shader);
    void draw(Shader *shader){};

private:
    void drawShaderData(Shader *shader);

private:
    GLuint m_texture0Id, m_texture1Id;
    GLuint m_planeVAO,m_planeVBO,m_cubeVAO,m_cubeVBO;
    Shader* depthShader;
    GLuint depthMapFBO;
    GLint defaultFBO;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
};

#endif // SHADOWMESH_H
