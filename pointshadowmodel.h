#ifndef POINTSHADOWMODEL_H
#define POINTSHADOWMODEL_H
#include "basemodel.h"
#include "pointshadowmesh.h"
#include "customcamera.h"
#include "qscopedpointer.h"

class PointShadowModel: public BaseModel
{
public:
    PointShadowModel();
    void draw(Shader* shader,QVector3D eyePos,GLuint cubeId);
};

#endif // POINTSHADOWMODEL_H
