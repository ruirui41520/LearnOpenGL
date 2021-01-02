#include "dispatcher.h"

Dispatcher::Dispatcher(QThread &thread)
    : m_targetThread(thread)
{
    moveToThread(&thread);
    connect(&thread, &QThread::finished, this, &QObject::deleteLater);
}
