#include <QGuiApplication>
// #include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // QQmlApplicationEngine engine;
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []()
    //     { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);
    // engine.loadFromModule("Play_with_Qml", "Main");

    return app.exec();
}
