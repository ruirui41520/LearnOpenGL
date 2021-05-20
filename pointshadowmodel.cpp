#include "pointshadowmodel.h"

PointShadowModel::PointShadowModel()
{
    m_meshs.append(new PointShadowMesh());
}

void PointShadowModel::draw(Shader *shader, QVector3D eyePos, GLuint cubeId)
{
    for(int i = 0;i < m_meshs.size();i++){
        BaseMesh* mesh = m_meshs.at(i);
        ((PointShadowMesh*)mesh)->drawWithVariab(shader, eyePos, cubeId);
    }
}
