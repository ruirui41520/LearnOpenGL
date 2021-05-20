#pragma once
#include "basescene.h"

BaseScene::BaseScene(CustomCamera *camera, QOpenGLWidget *widget)
{
    m_camera.reset(camera);
    m_widget.reset(widget);
}

BaseScene::~BaseScene(){}

int BaseScene::screenWidth()
{
    return m_widget.get()->width();
}

int BaseScene::screenHeight()
{
    return m_widget.get()->height();
}

QMatrix4x4 BaseScene::getViewMat()
{
    return m_camera.get()->getViewMatrix();
}

QMatrix4x4 BaseScene::getProjection()
{
    QMatrix4x4 m_projection;
    m_projection.perspective(m_camera.get()->zoom, 1.0f * screenWidth() / screenHeight(), 0.1f, 1000.0f);
    return m_projection;
}

QVector3D BaseScene::getViewPos(){
    return m_camera.get()->getPosition();
}

