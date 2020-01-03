#ifndef WINDOWUPDATER_H
#define WINDOWUPDATER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QQmlApplicationEngine>


class windowUpdater : public QObject
{
    Q_OBJECT
public:
    windowUpdater() {
        qDebug() << "Starting windowUpdater" << endl;
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
        qDebug() << "Something happened" << endl;
        if (worked) {
            emit tick(1);
        } else {
            emit tick(2);
        }
    }
};



class UpdaterInterface : public QObject {
    Q_OBJECT

public:

    static UpdaterInterface *getInstance();

signals:
    void updateGUI(int arg);

public slots:
    void hasWork(int arg) {
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
    UpdaterInterface() {
        worker = new windowUpdater();
        qDebug() << "Initializing Window Updater" << endl;
        worker->moveToThread(&myThread);
        connect(worker, &windowUpdater::tick, this, &UpdaterInterface::hasWork);
        myThread.start();
    }

    static UpdaterInterface *instance;
    QThread myThread;
    windowUpdater *worker;
};

#endif // WINDOWUPDATER_H
