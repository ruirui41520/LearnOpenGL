#pragma once
#include "shader.h"
#include "basemesh.h"
#include "cubemesh.h"
#include "planemesh.h"
#include "quadmesh.h"

class BaseModel
{
public:
    BaseModel();
    virtual void bindData(Shader* shader);
    virtual void draw(Shader* shader);

    public:
    QVector<BaseMesh*> m_meshs;
};
