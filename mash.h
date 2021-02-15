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
private:
    GLuint VAO,VBO,EBO;

    void setupMash();
};
