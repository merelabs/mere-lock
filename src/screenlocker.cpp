#include "screenlocker.h"
#include "lockscreen.h"

#include <QApplication>
Mere::Lock::ScreenLocker::~ScreenLocker()
{
    for(auto *screen : m_screens)
        delete screen;
}

Mere::Lock::ScreenLocker::ScreenLocker(QObject *parent) : QObject(parent)
{
    for(QScreen *screen : QApplication::screens())
    {
        auto *lockScreen = new Mere::Lock::LockScreen(screen);
        connect(lockScreen, &Mere::Lock::LockScreen::verified, this, [&](){
            emit verified();
        });
        m_screens.push_back(lockScreen);
    }
}

int Mere::Lock::ScreenLocker::lock()
{
    for(auto *screen : m_screens)
        screen->lock();

    emit locked();

    return 0;
}

int Mere::Lock::ScreenLocker::unlock()
{
    for(auto *screen : m_screens)
        screen->unlock();

    emit unlocked();

    return 0;
}
