#ifndef SHADOWMODEL_H
#define SHADOWMODEL_H
#include "basemodel.h"
#include "shadowmesh.h"

class ShadowModel:public BaseModel
{
public:
    ShadowModel();
    void drawWithPos(Shader* shader,QVector3D viewPos, int screenWidth,int screenHeight);
};

#endif // SHADOWMODEL_H
