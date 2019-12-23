#ifndef WINDOWUPDATER_H
#define WINDOWUPDATER_H

#include <QObject>
#include <QTimer>

class windowUpdater : public QObject
{
    Q_OBJECT
public:
    windowUpdater();
    QTimer *timer;
    bool worked = false;
    static windowUpdater *getInstance();

private:
    static windowUpdater *instance;

signals:
    void hasWork(int arg);
    void tick();

public slots:
    void tock();
};

#endif // WINDOWUPDATER_H
