#pragma once
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QImage>
#include "shader.h"
using namespace std;

struct Vertex{
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
//    // u向量
//    QVector3D Tangent;
//    // v向量
//    QVector3D Bitangent;
};

struct Texture{
    GLuint id;
    QString type;
    std::string path;
};

class Mash
{
public:
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    std::vector<Texture> textures;
    GLuint textureId;
    Mash(QVector<Vertex> vertices, QVector<unsigned int>indices, std::vector<Texture> textures);

    void draw(Shader *shader);
    void drawUseInstance(Shader *shader,int instanceCount);

public:
    GLuint VAO;

private:
    GLuint VBO,EBO;

private:
    void setupMash();
    void commonDraw(Shader *shader);
};
