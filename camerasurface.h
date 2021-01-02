#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H
#include <QObject>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

class CameraSurface: public QAbstractVideoSurface
{
     Q_OBJECT
public:
    explicit CameraSurface(QObject *parent = nullptr);
    ~CameraSurface();

    // QAbstractVideoSurface interface
public:
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const;
    bool present(const QVideoFrame &frame);

public:
   void  initialize();
};

#endif // CAMERASURFACE_H
