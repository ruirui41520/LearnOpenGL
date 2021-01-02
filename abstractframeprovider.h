#ifndef ABSTRACTFRAMEPROVIDER_H
#define ABSTRACTFRAMEPROVIDER_H
#include <QObject>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

class AbstractFrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)

public:
    AbstractFrameProvider(QObject *parent = nullptr);
    ~AbstractFrameProvider();
    QAbstractVideoSurface *videoSurface() const { return m_surface; }

public:
    void setVideoSurface(QAbstractVideoSurface *);
    void setFormat(int, int);
    void virtual onNewVideoContentReceived(QVideoFrame) = 0;

protected:
    QAbstractVideoSurface *m_surface;
    QVideoSurfaceFormat m_format;
};

#endif // ABSTRACTFRAMEPROVIDER_H
