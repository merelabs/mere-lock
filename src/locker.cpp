#include "locker.h"
#include "lockscreen.h"
#include "lockprompt.h"

#include <QDebug>
Mere::Lock::Locker::~Locker()
{

}

Mere::Lock::Locker::Locker(QObject *parent)
    : QObject(parent)
{
    m_screen = new LockScreen;
    connect(m_screen, &LockScreen::verified, this, [&](){
        unlock();
    });
}

int Mere::Lock::Locker::lock()
{
    m_screen->showFullScreen();
    return 0;
}

int Mere::Lock::Locker::unlock()
{
    emit unlocked();

    return 0;
}
