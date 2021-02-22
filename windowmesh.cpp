#include "windowmesh.h"

WindowMesh::WindowMesh(){}

void WindowMesh::initData(Shader *shader)
{
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    QVector<QVector3D> windows
    {
        QVector3D(-1.5f, 0.0f, -0.48f),
                QVector3D( 1.5f, 0.0f, 0.51f),
                QVector3D( 0.0f, 0.0f, 0.7f),
                QVector3D(-0.3f, 0.0f, -2.3f),
                QVector3D( 0.5f, 0.0f, -0.6f)
    };
    for (int i = 0; i < windows.size(); i++)
    {
        float distance = QVector3D(0,0,0).distanceToPoint(windows[i]);
        sorted[distance] = windows[i];
    }
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof (transparentVertices),transparentVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof (float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof (float),(void*)(3*sizeof (float)));
    glEnableVertexAttribArray(1);
    glGenTextures(1,&m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    QImage image = QImage(":/window.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true,true);
    if(!image.isNull()){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    shader->bind();
    shader->setInt("m_texutre",0);
    shader->release();
    glBindVertexArray(0);

}

void WindowMesh::draw(Shader *shader)
{
    Q_UNUSED(shader);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    QMatrix4x4 model = QMatrix4x4();
//    for (std::map<float, QVector3D>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//    {
//        model.translate(it->second);
//        shader->setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
    shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
