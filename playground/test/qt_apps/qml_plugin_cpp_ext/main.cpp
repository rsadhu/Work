#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mycustomclass.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register MyCustomClass as a QML component
    qmlRegisterType<MyCustomClass>("MyModule", 1, 0, "MyCustomClass");

    QQmlApplicationEngine engine;

    // Load the QML file
    const QUrl url(QStringLiteral("/Users/rakeshsadhu/dev/mygit/work/playground/test/qt_apps/qml_plugin_cpp_ext/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
