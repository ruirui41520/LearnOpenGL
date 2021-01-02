#ifndef SHADERTRANSFERUTIL_H
#define SHADERTRANSFERUTIL_H
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>
#include <QOffscreenSurface>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

class ShaderTransferUtil
{

public:
    ShaderTransferUtil(QOffscreenSurface *offscreenSurface);
    ~ShaderTransferUtil();
    void render(QOpenGLContext *share, QImage &input_image);

private:
    void initializeGL(QOpenGLContext *share);
    void compute();
    void checkGlError(QString content);

private:
    QScopedPointer<QOpenGLShaderProgram> m_computeProgram;
    QOffscreenSurface *m_offscreenSurface;
    QScopedPointer<QOpenGLContext> m_context;
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    bool isInitialized = false;
    int m_picWidth = 0;
    int m_picHeight = 0;
    GLuint m_inputTextureId = 0;
    unsigned char* streams;
};

#endif // SHADERTRANSFERUTIL_H
