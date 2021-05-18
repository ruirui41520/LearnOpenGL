#include "shadowmodel.h"

ShadowModel::ShadowModel()
{
    m_meshs.append(new ShadowMesh());
}

void ShadowModel::drawWithPos(Shader *shader, QVector3D viewPos,int width,int height)
{
    for(int i = 0;i < m_meshs.size();i++){
        BaseMesh* mesh = m_meshs.at(i);
        ((ShadowMesh*)mesh)->draw(shader,viewPos,width,height);
    }
}
