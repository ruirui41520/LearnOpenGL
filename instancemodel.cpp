#include "instancemodel.h"

InstanceModel::InstanceModel(QString path) : Model(path) {
  float radius = 150.0;
  float offset = 25.0f;
  for (int i = 0; i < modelCount; i++) {
    QMatrix4x4 model = QMatrix4x4();
    float angle = (float)i / (float)modelCount * 360.0f;
    float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float x = sin(angle) * radius + displacement;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float y = displacement * 0.4f;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float z = cos(angle) * radius + displacement;
    model.translate(QVector3D(x, y, z));
    float scale = (rand() % 20) / 100.0f + 0.05;
    model.scale(QVector3D(scale, scale, scale));
    float rotAngle = (rand() % 360);
    model.rotate(rotAngle, QVector3D(0.4f, 0.6f, 0.8f));
    modelMatrices.append(model);
  }
  applyInstanceData();
}

void InstanceModel::draw(Shader *shader) {
    for (int i = 0; i < m_meshes.size(); i++) {
        m_meshes[i].drawUseInstance(shader, modelCount);
    }
}

void InstanceModel::applyInstanceData() {
  GLuint buffer;
  int N = 4;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, modelCount * 4 *N * sizeof(float),
               modelMatrices.begin(), GL_STATIC_DRAW);
  for (int i = 0; i < m_meshes.size(); i++) {
    GLuint VAO = m_meshes.at(i).VAO;
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float) * N,
                          (void *)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float) * N,
                          (void *)(N*sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,4*sizeof(float) * N,
                          (void *)(2 *N* sizeof(float)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float) * N,
                          (void *)(3 * N*sizeof(float)));
    glVertexAttribDivisor(3,1);
    glVertexAttribDivisor(4,1);
    glVertexAttribDivisor(5,1);
    glVertexAttribDivisor(6,1);
    glBindVertexArray(0);
  }
}
