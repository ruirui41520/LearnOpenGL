#pragma once
#include "shader.h"
#include <QVector>
#include <QVector3D>
#include <QImage>

class BaseMesh
{
public:
    virtual void initData(Shader *shader){Q_UNUSED(shader)};
    virtual void draw(Shader* shader=nullptr){Q_UNUSED(shader)};

public:
    GLuint VAO,VBO;
};

