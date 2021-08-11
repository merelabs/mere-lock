#ifndef LOCKAPP_H
#define LOCKAPP_H

#include "locker.h"
#include "config.h"

#include <QDebug>
#include <QApplication>

class LockApp : public QApplication
{
    Q_OBJECT
public:
    ~LockApp();
    LockApp(int &argc, char **argv);

    int init();
    int start();

private:
    Mere::Lock::Locker *m_locker;
    Mere::Lock::Config *m_config;
};
#endif // LOCKAPP_H
