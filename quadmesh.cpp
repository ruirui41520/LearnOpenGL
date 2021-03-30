#include "quadmesh.h"

QuadMesh::QuadMesh() {}

void QuadMesh::initData(Shader *shader) {
    float quadVertices[] = {   // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                            // positions   // texCoords
                            -1.0f,  1.0f,  0.0f, 1.0f,
                            -1.0f, -1.0f,  0.0f, 0.0f,
                            1.0f, -1.0f,  1.0f, 0.0f,

                            -1.0f,  1.0f,  0.0f, 1.0f,
                            1.0f, -1.0f,  1.0f, 0.0f,
                            1.0f,  1.0f,  1.0f, 1.0f
    };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),(void *)(2 * sizeof(float)));
  shader->bind();
  shader->setInt("screenTexture", 0);
  shader->release();
  glBindVertexArray(0);
}

void QuadMesh::draw(Shader *shader) {
  Q_UNUSED(shader);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
