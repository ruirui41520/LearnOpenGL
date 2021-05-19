#include "pointshadowmesh.h"

PointShadowMesh::PointShadowMesh(){}

void PointShadowMesh::initData(Shader *shader)
{
    shader->bind();
    shader->setInt("diffuseTexture",0);
    shader->setInt("depthMap",1);
    shader->release();
}

void PointShadowMesh::draw(Shader *shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}
