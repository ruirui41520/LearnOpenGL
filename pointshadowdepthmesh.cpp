#include "pointshadowdepthmesh.h"

PointShadowDepthMesh::PointShadowDepthMesh(){}

void PointShadowDepthMesh::initData(Shader *shader)
{
    Q_UNUSED(shader);
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f),(float)SHADOW_WIDTH / (float)SHADOW_HEIGHT,near_plane,far_plane);
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
}

void PointShadowDepthMesh::draw(Shader *shader)
{
    shader->bind();
    for(int i = 0;i < 6;++i){
        shader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    }
    shader->setFloat("far_plane",far_plane);
    shader->setVec3("lightPos", lightPos);
    drawCube(shader);
    shader->release();
}

void PointShadowDepthMesh::drawCube(Shader *shader)
{
    glEnable(GL_CULL_FACE);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(5.0f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.75f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.75f));
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisable(GL_CULL_FACE);
}
