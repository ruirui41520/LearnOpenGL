#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <QObject>
#include <QThread>

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    Dispatcher(QThread &);

private:
    const QThread &m_targetThread;
};

#endif // DISPATCHER_H
