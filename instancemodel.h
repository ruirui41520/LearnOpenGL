#ifndef INSTANCEMODEL_H
#define INSTANCEMODEL_H
#include "model.h"
#include <QVector>

class InstanceModel:public Model
{
public:
    InstanceModel(QString path);
    void draw(Shader *shader);

private:
    void applyInstanceData();

private:
    QVector<QMatrix4x4> modelMatrices;
    int modelCount = 1000;
};

#endif // INSTANCEMODEL_H
