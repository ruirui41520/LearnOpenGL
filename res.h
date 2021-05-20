#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QVector3D>

const int SHADOW_WIDTH = 2048,SHADOW_HEIGHT =2048;
const float near_plane = 1.0f,far_plane = 25.0f;
const glm::vec3 lightPos = glm::vec3(0.0f,0.0f,0.0f);

