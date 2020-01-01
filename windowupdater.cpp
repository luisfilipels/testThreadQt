#include "windowupdater.h"
#include <QObject>
#include <QDebug>

UpdaterInterface *UpdaterInterface::instance = nullptr;

UpdaterInterface *UpdaterInterface::getInstance() {
        if (instance == nullptr) {
            qDebug() << "Creating interface" << endl;
            instance = new UpdaterInterface();
        } else {
            qDebug() << "Interface exists" << endl;
        }

        return instance;
    }

void UpdaterInterface::hasWork(int arg) {
    emit updateGUI(arg);
}
