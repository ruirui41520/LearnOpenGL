#include "mash.h"

Mash::Mash(QVector<Vertex> vertices, QVector<unsigned int> indices,
           std::vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  setupMash();
}

void Mash::draw(Shader *shader) {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for (uint i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    QString number;
    QString name = textures[i].type;
    if (name == "texture_diffuse") {
      number = QString::number(diffuseNr++);
    }else if (name == "texture_specular") {
         number = QString::number(specularNr++);
       }
    shader->setInt((name + number).toStdString().c_str(),i);
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glActiveTexture(GL_TEXTURE0);
}

void Mash::setupMash() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);
  // 顶点
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  // 法线
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, Normal));
  // 纹理
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, TexCoords));
  glBindVertexArray(0);
}
