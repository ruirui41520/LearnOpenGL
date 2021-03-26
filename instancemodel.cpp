#include "instancemodel.h"

InstanceModel::InstanceModel(QString path) : Model(path) {
  float radius = 100.0;
  float offset = 25.0f;
  modelMatrices = new glm::mat4[modelCount];
  for (uint i = 0; i < modelCount; i++) {
    glm::mat4 model = glm::mat4(1.0f);
    float angle = (float)i / (float)modelCount * 360.0f;
    float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float x = sin(angle) * radius + displacement;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float y = displacement * 0.4f - 15.0f;
    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    float z = cos(angle) * radius + displacement -100.0f;
    model = glm::translate(model, glm::vec3(x, y, z));
    // 2. scale: Scale between 0.05 and 0.25f
    float scale = (rand() % 20) / 100.0f + 0.05;
    model = glm::scale(model, glm::vec3(scale));
    // 3. rotation: add random rotation around a (semi)randomly picked rotation
    // axis vector
    float rotAngle = (rand() % 360);
    model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
    // 4. now add to list of matrices
    modelMatrices[i] = model;
  }
  applyInstanceData();
}

void InstanceModel::draw(Shader *shader) {
  glUniform1i(shader->uniformPosition("texture_diffuse1"), 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_loaded.at(0).id);
  for (int i = 0; i < m_meshes.size(); i++) {
    m_meshes[i].drawUseInstance(shader, modelCount);
  }
}

void InstanceModel::applyInstanceData() {
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, modelCount * sizeof(glm::mat4),
               &modelMatrices[0], GL_STATIC_DRAW);
  for (int i = 0; i < m_meshes.size(); i++) {
    glBindVertexArray(m_meshes.at(i).VAO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void *)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void *)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void *)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(aiMatrix4x4),
                          (void *)(3 * sizeof(glm::vec4)));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
  }
}
