#include "camerasurface.h"

CameraSurface::CameraSurface(QObject* parent) : QAbstractVideoSurface(parent)
{
}

CameraSurface::~CameraSurface()
{

}

void CameraSurface::initialize()
{

}

bool CameraSurface::present(const QVideoFrame &frame)
{
    Q_UNUSED( frame )
    return true;
}

QList<QVideoFrame::PixelFormat> CameraSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    if (type == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_BGRA32
                << QVideoFrame::Format_BGRA32_Premultiplied;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}
