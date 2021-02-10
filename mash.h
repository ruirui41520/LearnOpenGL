#pragma once
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
using namespace std;

struct Vertex{
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};

struct Texture{
    GLuint id;
    QString type;
    QString path;
};

class Mash
{
public:
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<Texture> textures;

    Mash(QVector<Vertex> vertices, QVector<unsigned int>indices, QVector<Texture> textures);

    void draw(QOpenGLShaderProgram *shader);

private:
    GLuint VAO,VBO,EBO;

    void setupMash();
};
