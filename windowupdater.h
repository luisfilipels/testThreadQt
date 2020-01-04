#ifndef WINDOWUPDATER_H
#define WINDOWUPDATER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QQmlApplicationEngine>


class WindowUpdater : public QObject
{
    Q_OBJECT
public:
    WindowUpdater() {
        qDebug() << "Creating WindowUpdater" << endl;
        timer = new QTimer();
        timer->setInterval(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(tock()));
        timer->start();
    }

    QTimer *timer;
    bool worked = false;

    char m_padding[7];

signals:
    void tick(int arg);

public slots:
    void tock() {
        qDebug() << "Updater thread : " << QThread::currentThreadId();
        qDebug() << " - Timer tick" << endl;
        if (worked) {
            emit tick(1);
        } else {
            emit tick(2);
        }
        worked = !worked;
    }
};



class UpdaterInterface : public QObject {

    Q_OBJECT

public:

    static UpdaterInterface *getInstance();

    UpdaterInterface() {
        worker = new WindowUpdater();
        qDebug() << "Initializing Window Updater" << endl;
        worker->moveToThread(&myThread);
        connect(worker, &WindowUpdater::tick, this, &UpdaterInterface::hasWork);
        myThread.start();
    }

signals:
    void updateGUI(int arg);

public slots:
    void hasWork(int arg) {
        qDebug() << "Interface thread : " << QThread::currentThreadId();
        qDebug() << " - Update GUI" << endl;
        emit updateGUI(arg);
    }

    static QObject *UpdaterInterfaceProvider (QQmlEngine *engine, QJSEngine *scriptEngine) {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)

            qDebug() << "Entered provider" << endl;

            UpdaterInterface *updater = UpdaterInterface::getInstance();
            return updater;
        }


private:


    static UpdaterInterface *instance;
    QThread myThread;
    WindowUpdater *worker;
};

#endif // WINDOWUPDATER_H
