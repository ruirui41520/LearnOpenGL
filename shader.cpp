#include "shader.h"

Shader::Shader(QString verFilePath, QString fragFilePath,
               QString geometryPath) {
  m_program = new QOpenGLShaderProgram();
  m_programId = m_program->programId();
  bool success = m_program->addCacheableShaderFromSourceFile(
      QOpenGLShader::Vertex, verFilePath);
  if (!success) {
    glError("addCacheableShaderFromSourceVertex");
  }
  success = m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
                                                        fragFilePath);
  if (!success) {
    glError("addCacheableShaderFromSourceFile");
  }
  m_program->link();
}

GLint Shader::uniformPosition(QString name) {
  return m_program->uniformLocation(name);
}

GLuint Shader::shaderId() { return m_programId; }

void Shader::setProjection(QMatrix4x4 projectionMatrix) {
  m_projection = projectionMatrix;
}

void Shader::setView(QMatrix4x4 viewMatrix) { m_view = viewMatrix; }

void Shader::setBool(QString name, bool value) const {
  m_program->setUniformValue(name.toStdString().c_str(), (int)value);
}

void Shader::setInt(QString name, int value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

void Shader::setFloat(QString name, float value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

void Shader::setVec2(QString name, const QVector2D &value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

void Shader::setVec2(QString name, float x, float y) const {
  m_program->setUniformValue(name.toStdString().c_str(), x, y);
}

void Shader::setVec3(QString name, QVector3D &value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

void Shader::setVec3(QString name, float x, float y, float z) const {
  m_program->setUniformValue(name.toStdString().c_str(), x, y, z);
}

void Shader::setVec4(QString name, QVector4D &value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

void Shader::setVec4(QString name, float x, float y, float z, float w) const {
  m_program->setUniformValue(name.toStdString().c_str(), x, y, z, w);
}

void Shader::setMat4(QString name, QMatrix4x4 &value) const {
  m_program->setUniformValue(name.toStdString().c_str(), value);
}

QMatrix4x4 Shader::projection()
{
    return m_projection;
}

QMatrix4x4 Shader::view()
{
    return m_view;
}

void Shader::glError(QString content) {
  if (GLenum err; (err = glGetError()) != GL_NO_ERROR) {
    qWarning() << "********" << content << "error :" << Qt::hex << err;
  }
}
