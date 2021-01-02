#include "abstractframeprovider.h"

AbstractFrameProvider::AbstractFrameProvider(QObject *parent) : QObject(parent)
{
    m_surface = nullptr;
}

AbstractFrameProvider::~AbstractFrameProvider()
{
}

void AbstractFrameProvider::setFormat(int width, int heigth)
{
    QSize size(width, heigth);
    QVideoSurfaceFormat format(size, QVideoFrame::Format_ARGB32);
    m_format = format;

    if (m_surface) {
        if (m_surface->isActive()) {
            m_surface->stop();
        }
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void AbstractFrameProvider::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface && m_surface != surface  && m_surface->isActive()) {
        m_surface->stop();
    }

    m_surface = surface;

    if (m_surface && m_format.isValid()) {
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

