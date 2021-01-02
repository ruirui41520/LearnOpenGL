#include "shadertransferutil.h"

ShaderTransferUtil::ShaderTransferUtil(QOffscreenSurface *offscreenSurface)
    : m_context(nullptr), m_vbo(nullptr), m_vao(nullptr),
      m_offscreenSurface(offscreenSurface) {}

ShaderTransferUtil::~ShaderTransferUtil() {
  m_context.get()->makeCurrent(m_offscreenSurface);
  delete m_vbo;
  delete m_vao;
  m_context->doneCurrent();
}

void ShaderTransferUtil::render(QOpenGLContext *share, QImage &input_image) {
  if (input_image.bits() == nullptr) {
    qWarning() << "empty input data";
  }
  m_picWidth = input_image.width();
  m_picHeight = input_image.height();
  if (!isInitialized) {
    initializeGL(share);
    isInitialized = true;
  }
}

void ShaderTransferUtil::initializeGL(QOpenGLContext *targetContext) {
  m_context.reset(targetContext);
//  m_context->setShareContext(share);
//  m_context->setFormat(share->format());
  m_context->create();
  if (!m_context->makeCurrent(m_offscreenSurface))
    return;
  QOpenGLFunctions *f = m_context->functions();
  f->glGenBuffers(1, &m_inputTextureId);
//  checkGlError("glGenBuffers");
}

void ShaderTransferUtil::compute() {
  glViewport(0, 0, m_picWidth, m_picHeight);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  //    glBindBuffer(GL_TEXTURE_2D,m_inputTextureId);
  //    glTexImage2D(GL_TEXTURE_2D, 0,
  //    GL_RGBA,m_picWidth,m_picHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,bits);
  //    m_computeProgram->bind();
  //    m_computeProgram->setUniformValue("inputTexture",m_inputTextureId);
  //    m_computeProgram->setUniformValue("width",m_picWidth);
  //    m_computeProgram->setUniformValue("height",m_picHeight);
  //    glDispatchCompute(m_picWidth / 8,m_picHeight / 8, 1);
}

void ShaderTransferUtil::checkGlError(QString content) {
  if (GLenum error; (error = glGetError()) != GL_NO_ERROR) {
    qWarning() << "*****  = " << content << Qt::hex << error;
  }
}
