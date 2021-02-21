#include "planemesh.h"

PlaneMesh::PlaneMesh(){}

void PlaneMesh::initData(Shader *shader)
{
    float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 5*sizeof (float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 5*sizeof (float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    QImage image = QImage(":/awesomeface.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true, true);
    if(!image.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    shader->bind();
    shader->setInt("m_texture",0);
    shader->release();
    glBindVertexArray(0);
}

void PlaneMesh::draw(Shader *shader)
{
    Q_UNUSED(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
