#include "renderframeprovider.h"
#include <QApplication>
#include <QDebug>

RenderFrameProvider::RenderFrameProvider(QObject *parent)
    : AbstractFrameProvider(parent) {
  m_surface = nullptr;
  m_initialized = false;
  // init FrameDispatcher
  m_frameDispatcher = new FrameDispatcher(m_workerThread, this);
  // init off screen open gl
  m_offscreenSurface.reset(new QOffscreenSurface(nullptr, this));
  m_offscreenSurface->create();
  m_context.reset(new QOpenGLContext);
  m_context->create();
  m_context->moveToThread(&m_workerThread);
  m_transfer = new ShaderTransferUtil(m_offscreenSurface.get());

  //     connect signals
  connect(this, &RenderFrameProvider::frameReady, m_frameDispatcher,
          &FrameDispatcher::processVideoFrame);

  m_workerThread.start();
}

RenderFrameProvider::~RenderFrameProvider() {
  m_workerThread.quit();
  m_workerThread.wait();
}

void RenderFrameProvider::onNewVideoContentReceived(QVideoFrame frame) {
  if (!m_surface)
    return;

  QApplication::removePostedEvents(m_frameDispatcher, QEvent::MetaCall);
  emit frameReady(frame);
  // Lock
  std::lock_guard<std::mutex> lock(m_frameMutex);
  m_surface->present(m_curFrame);
}

void RenderFrameProvider::processVideoFrame(QVideoFrame &frame) {
  if (!m_initialized) {

    m_context->makeCurrent(m_offscreenSurface.get());
    auto mainContext = QOpenGLContext::currentContext();
    m_context->setFormat(mainContext->format());
    m_offscreenSurface->setFormat(mainContext->format());
    initializeOpenGLFunctions();

    m_initialized = true;
  }

  frame.map(QAbstractVideoBuffer::ReadOnly);

  // Convert current QVideoFrame to QImage
  QImage::Format format =
      QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
  QImage currentImage;
  if (format != QImage::Format_Invalid) {
    currentImage = QImage(frame.bits(), frame.width(), frame.height(), format);
  } else {
    currentImage = frame.image();
  }

  {
    std::lock_guard<std::mutex> lock(m_frameMutex);
    m_curFrame = currentImage;
    if(!currentImage.isNull()){
        m_transfer->render(m_context.get(), currentImage);
    }
  }

  frame.unmap();
}

FrameDispatcher::FrameDispatcher(QThread &targetThread,
                                 RenderFrameProvider *frameProvider)
    : Dispatcher(targetThread), m_frameProvider(frameProvider) {}

void FrameDispatcher::processVideoFrame(QVideoFrame input) {
  m_frameProvider->processVideoFrame(input);
}

FrameDispatcher::~FrameDispatcher() {}
