# LearnOpenGL
int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
//    registerQMLType();
//    m_mainWindow = new QQuickView;
//    m_mainWindow->setResizeMode(QQuickView::SizeRootObjectToView);
//    QObject::connect(m_mainWindow, SIGNAL( destroyed() ), &app, SLOT( quit() ));
//    QObject::connect(m_mainWindow->engine(), &QQmlEngine::quit,
//                     qApp, &QApplication::quit);

//    m_mainWindow->setSource(QUrl("qrc:/main.qml"));
//    m_mainWindow->resize(890, 652);
//    m_mainWindow->setMinimumWidth(650);
//    m_mainWindow->setMinimumHeight(652);
//    m_mainWindow->setTitle("OpenglDemo test");
//    m_mainWindow->show();
//    startCamera();

    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);
    CustomOpenglWidget widget;
    widget.setWindowTitle(QObject::tr("CustomGLWidget"));
    widget.show();

    return app.exec();
}
