TEMPLATE = app
QT += quick multimedia widgets opengl multimediawidgets gui

CONFIG += c++17


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        abstractframeprovider.cpp \
        basemodel.cpp \
        camerasurface.cpp \
        cubemesh.cpp \
        cubemodel.cpp \
        customcamera.cpp \
        customopenglwidget.cpp \
        dispatcher.cpp \
        main.cpp \
        mash.cpp \
        model.cpp \
        planemesh.cpp \
        planemodel.cpp \
        renderframeprovider.cpp \
        shader.cpp \
        shadertransferutil.cpp \
        skymesh.cpp \
        skymodel.cpp \
        videocontainer.cpp \
        windowmesh.cpp \
        windowmodel.cpp

RESOURCES += qml.qrc \
    image.qrc \
    shader.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstractframeprovider.h \
    basemesh.h \
    basemodel.h \
    camerasurface.h \
    cubemesh.h \
    cubemodel.h \
    customcamera.h \
    customopenglwidget.h \
    dispatcher.h \
    mash.h \
    model.h \
    planemesh.h \
    planemodel.h \
    renderframeprovider.h \
    shader.h \
    shadertransferutil.h \
    skymesh.h \
    skymodel.h \
    videocontainer.h \
    windowmesh.h \
    windowmodel.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/assimp/5.0.1/lib/release/ -lassimp.5.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/assimp/5.0.1/lib/debug/ -lassimp.5.0.0
else:unix: LIBS += -L$$PWD/../../../../../usr/local/Cellar/assimp/5.0.1/lib/ -lassimp.5.0.0

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/assimp/5.0.1/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/assimp/5.0.1/include
