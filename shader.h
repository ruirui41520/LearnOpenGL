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
#include <glm/glm.hpp>

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
    GLuint shaderId() const;
    void setBool(QString name,bool value) const;
    void setInt(QString name,int value) const;
    void setFloat(QString name,float value) const;
    void setVec2(QString name,const QVector2D &value) const;
    void setVec2(QString name,float x,float y) const;
    void setVec3(QString name,const QVector3D &value) const;
    void setVec3(QString name,float x,float y,float z)const;
    void setVec4(QString name,QVector4D &value) const;
    void setVec4(QString name,float x,float y,float z,float w)const;
    void setMat4(QString name,QMatrix4x4 &value)const;
    void glError(QString content);

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(shaderId(), name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderId(), name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(shaderId(), name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderId(), name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(shaderId(), name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(shaderId(), name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    QOpenGLShaderProgram* m_program;
    GLuint m_programId;

};

#endif // SHADER_H
