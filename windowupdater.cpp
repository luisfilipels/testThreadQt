#include "windowupdater.h"
#include <QObject>
#include <QDebug>
windowUpdater::windowUpdater()
{
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(tock()));
    timer->start();
}

windowUpdater *windowUpdater::instance = nullptr;

windowUpdater *windowUpdater::getInstance() {
        if (instance == nullptr) {
            instance = new windowUpdater();
        }
        return instance;
    }


void windowUpdater::tock() {
    qDebug() << "AAAAAAAA" << endl;
    if (worked) {
        emit hasWork(1);
        worked = false;
    } else {
        emit hasWork(2);
        worked = true;
    }
}
