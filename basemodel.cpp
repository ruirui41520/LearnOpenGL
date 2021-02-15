#include "basemodel.h"

BaseModel::BaseModel() {}

void BaseModel::bindData(Shader *shader) {
    for(int i = 0;i < m_meshs.size();i++){
        BaseMesh* mesh = m_meshs.at(i);
        mesh->initData(shader);
    }
}

void BaseModel::draw(Shader *shader) {
    for(int i = 0;i < m_meshs.size();i++){
        BaseMesh* mesh = m_meshs.at(i);
        mesh->draw(shader);
    }
}
