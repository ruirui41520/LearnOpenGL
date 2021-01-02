#include "capturepermission.h"
#import <AVFoundation/AVCaptureDevice.h>
#import <AppKit/AppKit.h>
#include <QDebug>

#include <QaCore>

CapturePermission::CapturePermission(): QObject()
{
}

void CapturePermission::requestPermission()
{
    if(@available(macos 10.14, *))
    {
        NSApp.appearance = [NSAppearance appearanceNamed: NSAppearanceNameDarkAqua];
        switch ([AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo])
        {
        case AVAuthorizationStatusAuthorized:
        {
            // The user has previously granted access to the camera.
            qInfo() << "The user has previously granted access to the camera";
            emit cameraPermission(true);
            break;
        }
        case AVAuthorizationStatusNotDetermined:
        {
            // The app hasn't yet asked the user for camera access.
            [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
                                         qWarning() << "The app hasn't yet asked the user for camera access " << granted;
                                         emit cameraPermission(granted);

                                         return;
                                     }];
            break;
        }
        case AVAuthorizationStatusDenied:
        {
            // The user has previously denied access.
            qCritical() << "The user has previously denied access";
            emit cameraPermission(false);
            break;
        }
        case AVAuthorizationStatusRestricted:
        {
            // The user can't grant access due to restrictions.
            qCritical() << "The user can't grant access due to restrictions";
            emit cameraPermission(false);
            break;
        }
        }
    }
    else
    {
        emit cameraPermission(true);
    }
}
