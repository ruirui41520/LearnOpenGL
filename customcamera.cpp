#include "customcamera.h"

CustomCamera::CustomCamera(QVector3D position, QVector3D up, float yaw,
                           float pitch) {
  m_sensitive = SENSITIVITY;
  zoom = ZOOM;
  m_movespeed = SPEED;
  m_position = position;
  world_up = up;
  m_yaw = yaw;
  m_spitch = pitch;
  m_front = -position;
  updateCameraVectors();
  for (uint i = 0; i != 1024; i++) {
    keys[i] = false;
  }
}

CustomCamera::~CustomCamera() {}

QMatrix4x4 CustomCamera::getViewMatrix() {
  QMatrix4x4 view;
  view.lookAt(m_position, m_position + m_front, m_up);
  return view;
}

void CustomCamera::processMouseScroll(float offset) {
  if (zoom >= 1.0f && zoom <= 45.0f) {
    zoom -= offset;
  }
  if (zoom > 45.0f) {
    zoom = 45.0f;
  } else if (zoom < 1.0f) {
    zoom = 1.0f;
  }
}

void CustomCamera::processMouseMovement(float xOffset, float yOffset) {
  xOffset *= m_sensitive;
  yOffset *= m_sensitive;
  m_yaw += xOffset;
  m_spitch += yOffset;
  if (m_spitch > 89.0f) {
    m_spitch = 89.0f;
  } else if (m_spitch < -89.0f) {
    m_spitch = -89.0f;
  }
  updateCameraVectors();
}

void CustomCamera::processInput(float timeDuration) {
  if (keys[Qt::Key_W]) {
    processKeyboard(FORWARD, timeDuration);
  } else if (keys[Qt::Key_S]) {
    processKeyboard(BACKWARD, timeDuration);
  } else if (keys[Qt::Key_A]) {
    processKeyboard(LEFT, timeDuration);
  } else if (keys[Qt::Key_D]) {
    processKeyboard(RIGHT, timeDuration);
  } else if (keys[Qt::Key_E]) {
    processKeyboard(UP, timeDuration);
  } else if (keys[Qt::Key_Q]) {
    processKeyboard(DOWN, timeDuration);
  }
}

void CustomCamera::processKeyboard(Camera_Movement action, float deltaTime) {
  float velocity = this->m_movespeed * deltaTime;
  switch (action) {
  case FORWARD:
    m_position += m_front * velocity;
    break;
  case BACKWARD:
    m_position -= m_front * velocity;
    break;
  case RIGHT:
    m_position += m_right * velocity;
    break;
  case LEFT:
    m_position -= m_right * velocity;
    break;
  case UP:
    m_position += m_up * velocity;
    break;
  case DOWN:
    m_position -= m_up * velocity;
    break;
  }
}

void CustomCamera::updateCameraVectors() {
  QVector3D localFront;
  localFront.setX(cos(m_yaw) * cos(m_spitch));
  localFront.setY(sin(m_spitch));
  localFront.setZ(sin(m_yaw) * cos(m_spitch));
  m_front = localFront.normalized();
  m_right = QVector3D::crossProduct(m_front, world_up).normalized();
  m_up = QVector3D::crossProduct(m_right, m_front).normalized();
}
