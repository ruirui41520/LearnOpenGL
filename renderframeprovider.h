#ifndef RENDERFRAMEPROVIDER_H
#define RENDERFRAMEPROVIDER_H
#include "dispatcher.h"
#include <QThread>
#include <QObject>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLTexture>
#include "abstractframeprovider.h"
#include <QOpenGLFunctions_3_3_Core>
#include "shadertransferutil.h"
class FrameDispatcher;

class RenderFrameProvider: public AbstractFrameProvider, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
public:
    RenderFrameProvider(QObject *parent = nullptr);
    ~RenderFrameProvider();

    void processVideoFrame( QVideoFrame& frame );

Q_SIGNALS:
    void frameReady( QVideoFrame input );

    // AbstractFrameProvider interface
public slots:
    void onNewVideoContentReceived(QVideoFrame);

private:
    FrameDispatcher *m_frameDispatcher;
    QThread m_workerThread;
    bool m_initialized;
    QScopedPointer<QOpenGLContext> m_context;
    QScopedPointer<QOffscreenSurface> m_offscreenSurface;
    QImage m_curFrame;
    std::mutex m_frameMutex;
    ShaderTransferUtil *m_transfer;

};

class FrameDispatcher final : public Dispatcher
{
    Q_OBJECT
public:
    FrameDispatcher(QThread &, RenderFrameProvider *);
    virtual ~FrameDispatcher() override;

private:
    RenderFrameProvider* m_frameProvider;

public slots:
    void processVideoFrame( QVideoFrame input );
};

#endif // RENDERFRAMEPROVIDER_H
