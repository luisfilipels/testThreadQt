#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QObject>
#include <QQmlContext>
#include "windowupdater.h"

static QObject *windowUpdaterProvider (QQmlEngine *engine, QJSEngine *scriptEngine) {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        windowUpdater *updater = windowUpdater::getInstance();
        return updater;
    }


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;



    qmlRegisterSingletonType<windowUpdater>("threadtest", 1, 0, "Updater", windowUpdaterProvider);

    windowUpdater *updater = windowUpdater::getInstance();
    QThread *thread = new QThread;
    updater->moveToThread(thread);
    thread->start();
    //qmlRegisterType<windowUpdater>("threadtest", 1, 0, "Updater");

    engine.rootContext()->setContextProperty("threadtest",updater);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
