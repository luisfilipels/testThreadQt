#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QObject>
#include <QQmlContext>
#include "windowupdater.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qDebug() << "Starting application" << endl;

    //UpdaterInterface::getInstance();

    auto x = qmlRegisterSingletonType<UpdaterInterface>("Threadtest", 1, 0, "Updater", UpdaterInterface::UpdaterInterfaceProvider);

    qDebug() << "Value of x: " << x << endl;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
