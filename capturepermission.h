#ifndef CAPTUREPERMISSION_H
#define CAPTUREPERMISSION_H


#include <QObject>

class CapturePermission: public QObject
{
    Q_OBJECT

public:
    CapturePermission();
    void requestPermission();

signals:
    void cameraPermission(bool);
};

#endif // CAPTUREPERMISSION_H
