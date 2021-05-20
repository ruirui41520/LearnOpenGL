#include "pointshadowmesh.h"

PointShadowMesh::PointShadowMesh(){}

void PointShadowMesh::initData(Shader *shader)
{
    glGenTextures(1, &woodTextureId);
    glBindTexture(GL_TEXTURE_2D,woodTextureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    QImage image = QImage(":/textures/wood.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true,true);
    if(!image.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    shader->bind();
    shader->setInt("diffuseTexture",0);
//    shader->setInt("depthCube",1);
    shader->release();
}

void PointShadowMesh::drawWithVariab(Shader *shader, QVector3D eyePos, GLuint cubeId)
{
    shader->bind();
    shader->setVec3("lightPos",lightPos);
    shader->setVec3("viewPos", eyePos);
    shader->setFloat("far_plane",far_plane);
    shader->setBool("useShadows", true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,woodTextureId);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeId);
    drawCube(shader);
    shader->release();
}

void PointShadowMesh::drawCube(Shader *shader)
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
