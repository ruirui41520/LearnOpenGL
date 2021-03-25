#include "instancemodel.h"

InstanceModel::InstanceModel(QString path) : Model(path) {
  float radius = 200.0f;
  float offset = 25.0f;
  for (int i = 0; i < modelCount; i++) {
    QMatrix4x4 model = QMatrix4x4();
    float angle = (float)i / (float)modelCount * 360.0f;
    float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float x = cos(angle) * radius + displacement;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float y = displacement * 0.2f;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float z = sin(angle) * radius + displacement;
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
    glUniform1i(shader->uniformPosition("texture_diffuse1"), 0);
    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture_loaded.at(0).id);
    glBindTexture(GL_TEXTURE_2D, textureId);
    for (int i = 0; i < m_meshes.size(); i++) {
        m_meshes[i].drawUseInstance(shader, modelCount);
    }
}

void InstanceModel::applyInstanceData() {
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, modelCount * sizeof(aiMatrix4x4), modelMatrices.begin()->data(), GL_STATIC_DRAW);
  for (int i = 0; i < m_meshes.size(); i++) {
    glBindVertexArray(m_meshes.at(i).VAO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(aiMatrix4x4),
                          (void *)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(aiMatrix4x4),
                          (void *)(sizeof(QVector4D)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,sizeof(aiMatrix4x4),
                          (void *)(2*sizeof(QVector4D)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(aiMatrix4x4),
                          (void *)(3*sizeof(QVector4D)));
    glVertexAttribDivisor(3,1);
    glVertexAttribDivisor(4,1);
    glVertexAttribDivisor(5,1);
    glVertexAttribDivisor(6,1);
    glBindVertexArray(0);
  }
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  QImage img1 = QImage(":/container.jpg").convertToFormat(QImage::Format_RGB888);
  if (!img1.isNull()) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img1.width(), img1.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img1.bits());
      glGenerateMipmap(GL_TEXTURE_2D);
  }
}
