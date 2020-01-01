#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QObject>
#include <QQmlContext>
#include "windowupdater.h"

static QObject *UpdaterInterfaceProvider (QQmlEngine *engine, QJSEngine *scriptEngine) {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        qDebug() << "Entered provider" << endl;

        UpdaterInterface *updater = UpdaterInterface::getInstance();
        return updater;
    }


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qDebug() << "Starting application" << endl;

    qmlRegisterSingletonType<UpdaterInterface>("threadtest", 1, 0, "Updater", UpdaterInterfaceProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
