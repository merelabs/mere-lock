#include "screenlocker.h"
#include "config.h"
#include "ticker.h"
#include "lockscreen.h"
#include "screenunlocker.h"

#include <QApplication>
Mere::Lock::ScreenLocker::~ScreenLocker()
{
    for(auto *screen : m_screens)
        delete screen;

    if (m_ticker)
    {
        delete m_ticker;
        m_ticker = nullptr;
    }
}

Mere::Lock::ScreenLocker::ScreenLocker(QObject *parent)
    : QObject(parent),
      m_ticker(new Mere::Lock::Ticker(1, this)),
      m_config(Mere::Lock::Config::instance())
{
    for(QScreen *screen : QApplication::screens())
    {
        auto *lockScreen = new Mere::Lock::LockScreen(screen);
        m_screens.push_back(lockScreen);
    }

    m_screen = m_screens.at(0);

    m_unlocker = new Mere::Lock::ScreenUnlocker(m_screen, this);
    connect(m_unlocker, &Mere::Lock::Unlocker::blocked, this, [&](){
        block();
    });

    connect(m_unlocker, &Mere::Lock::Unlocker::unblocked, this, [&](){
        unblock();
    });

    connect(m_unlocker, &Mere::Lock::Unlocker::unlocked, this, [&](){
        release();
        emit unlocked();
    });

    connect(m_unlocker, &Mere::Lock::Unlocker::cancelled, this, [&](){
        restore();
    });

    connect(m_ticker, &Mere::Lock::Ticker::tick, this, [&](){
        tick();
    });

    m_ticker->start();

    m_screen->setFocusPolicy(Qt::StrongFocus);
    m_screen->setFocus(Qt::ActiveWindowFocusReason);
    m_screen->installEventFilter(this);
}

int Mere::Lock::ScreenLocker::lock()
{
    for(auto *screen : m_screens)
        screen->lock();

    capture();

    emit locked();

    return 0;
}

int Mere::Lock::ScreenLocker::unlock()
{
    for(auto *screen : m_screens)
        screen->unlock();

    release();

    m_unlocker->unlock();

//    m_ticker->stop();

//    emit unlocked();

    return 0;
}

void Mere::Lock::ScreenLocker::restore()
{
    for(auto *screen : m_screens)
        screen->restore();

    capture();
}

int Mere::Lock::ScreenLocker::block()
{
    for(auto *screen : m_screens)
        screen->block();

    capture();

    return 0;
}

int Mere::Lock::ScreenLocker::unblock()
{
    for(auto *screen : m_screens)
        screen->unblock();

    return 0;
}

void Mere::Lock::ScreenLocker::tick()
{
    for(auto *screen : m_screens)
        screen->tick();
}

void Mere::Lock::ScreenLocker::capture()
{
    m_screen->grabMouse();
    m_screen->grabKeyboard();
}

void Mere::Lock::ScreenLocker::release()
{
    m_screen->releaseMouse();
    m_screen->releaseKeyboard();
}

bool Mere::Lock::ScreenLocker::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() == QEvent::KeyPress || event->type() == QEvent::MouseMove)
         &&  m_unlocker->state() != Mere::Lock::Unlocker::InProgress)
    {
#ifdef QT_DEBUG
        // - test code
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            ::exit(0);
        // - end of test code
#endif

        if (m_unlocker->attempt() < m_config->attempts())
            unlock();

        return true;
    }

    return false;
}
