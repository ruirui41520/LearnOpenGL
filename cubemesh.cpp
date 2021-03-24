#include "cubemesh.h"

CubeMesh::CubeMesh() {}

void CubeMesh::initData(Shader *shader) {
    float positions[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    float texture[] = {
        // positions          // texture Coords
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (positions) + sizeof (texture), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (positions), &positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof (positions), sizeof (texture), &texture);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof (float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 2*sizeof (float), (void*)(sizeof(positions)));
    glEnableVertexAttribArray(1);
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    QImage image = QImage(":/container2.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true, true);
    if(!image.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    GLuint m_uniformBlockCube = glGetUniformBlockIndex(shader->shaderId(), "Matrices");
    glUniformBlockBinding(shader->shaderId(),m_uniformBlockCube,0);
    glGenBuffers(1,&m_uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER,m_uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER,32*sizeof (float),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferRange(GL_UNIFORM_BUFFER,0,m_uboMatrices,0 , 2*sizeof (QMatrix4x4().data()));

    shader->bind();
    shader->setInt("m_texture",0);
    shader->release();
    glBindVertexArray(0);
}

void CubeMesh::draw(Shader *shader) {
    Q_UNUSED(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER,0, 16*sizeof (float), shader->projection().data());
    glBufferSubData(GL_UNIFORM_BUFFER, 16*sizeof (float),16*sizeof (float), shader->view().data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
