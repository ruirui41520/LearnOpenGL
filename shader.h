#ifndef SHADER_H
#define SHADER_H
#include <QString>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QVector3D>
#include <QScopedPointer>
#include <QMatrix>
#include <QMatrix4x4>
#include <QDebug>
#include <QOpenGLFunctions_3_2_Core>
#include "customcamera.h"

class Shader
{
public:
    Shader(QString verFilePath,QString fragFilePath, QString geometryPath = nullptr);
    void bind(){
        m_program->bind();
    }
    void release(){
        m_program->release();
    }
    GLint uniformPosition(QString name);
    GLuint shaderId();
    void setProjection(QMatrix4x4 projectionMatrix);
    void setView(QMatrix4x4 viewMatrix);
    void setBool(QString name,bool value) const;
    void setInt(QString name,int value) const;
    void setFloat(QString name,float value) const;
    void setVec2(QString name,const QVector2D &value) const;
    void setVec2(QString name,float x,float y) const;
    void setVec3(QString name,QVector3D &value) const;
    void setVec3(QString name,float x,float y,float z)const;
    void setVec4(QString name,QVector4D &value) const;
    void setVec4(QString name,float x,float y,float z,float w)const;
    void setMat4(QString name,QMatrix4x4 &value)const;
    void glError(QString content);
    QMatrix4x4 projection();
    QMatrix4x4 view();

private:
    QOpenGLShaderProgram* m_program;
    GLuint m_programId;
    QMatrix4x4 m_projection, m_view;

};

#endif // SHADER_H
