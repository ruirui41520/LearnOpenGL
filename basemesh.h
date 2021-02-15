#pragma once
#include "shader.h"

class BaseMesh
{
public:
    virtual void initData(Shader *shader){Q_UNUSED(shader)};
    virtual void draw(Shader* shader=nullptr){Q_UNUSED(shader)};

public:
    GLuint VAO,VBO;
};

