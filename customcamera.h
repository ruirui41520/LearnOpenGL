#ifndef CUSTOMCAMERA_H
#define CUSTOMCAMERA_H
#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <math.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;

class CustomCamera
{
public:
    CustomCamera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f),
                 float yaw = YAW, float pitch = PITCH);
    ~CustomCamera();
    QMatrix4x4 getViewMatrix();
    void processMouseScroll(float offset);
    void processMouseMovement(float xOffset,float yOffset);
    void processInput(float timeDuration);
    QVector3D getPosition();


private:
    void processKeyboard(Camera_Movement action,float deltaTime);
    void updateCameraVectors();
public:
    float zoom;
    bool keys[1024];

private:
    QVector3D m_position,m_front,m_up,m_right,world_up;
    float m_sensitive,m_movespeed;
    float m_yaw,m_spitch;


};

#endif // CUSTOMCAMERA_H
