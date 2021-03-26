#ifndef INSTANCEMODEL_H
#define INSTANCEMODEL_H
#include "model.h"
#include <QVector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class InstanceModel: public Model
{
public:
    InstanceModel(QString path);
    void draw(Shader *shader);

private:
    void applyInstanceData();

private:
    glm::mat4* modelMatrices;;
    uint modelCount = 10000;
    GLuint buffer;
};

#endif // INSTANCEMODEL_H
