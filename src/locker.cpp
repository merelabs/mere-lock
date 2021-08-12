#include "locker.h"
#include "lockscreen.h"

#include <QApplication>
Mere::Lock::Locker::~Locker()
{
    for(auto *screen : m_screens)
        delete screen;
}

Mere::Lock::Locker::Locker(QObject *parent)
    : QObject(parent)
{
    for(QScreen *screen : QApplication::screens())
    {
        auto *s = new LockScreen(screen);
        connect(s, &LockScreen::verified, this, [&](){
            unlock();
        });
        m_screens.push_back(s);
    }
}

int Mere::Lock::Locker::lock()
{
    for(auto *screen : m_screens)
        screen->lock();

    return 0;
}

int Mere::Lock::Locker::unlock()
{
    emit unlocked();

    return 0;
}
