#include "screenlocker.h"
#include "config.h"
#include "ticker.h"
#include "lockscreen.h"
#include "lockprompt.h"
#include "screenunlocker.h"

#include <QEventLoop>
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
    connect(m_ticker, &Mere::Lock::Ticker::tick, [&]{
        tick();
    });

    m_ticker->start();

    m_screen->setFocusPolicy(Qt::StrongFocus);
    m_screen->setFocus(Qt::ActiveWindowFocusReason);
}

int Mere::Lock::ScreenLocker::lock()
{
    for(auto *screen : m_screens)
        screen->lock();

    // if user does not provide value
    // for -p/--password option, ask it.
    if (m_config->ask() && this->ask())
        return 1;

    capture();

    return 0;
}

int Mere::Lock::ScreenLocker::unlock()
{
    for(auto *screen : m_screens)
        screen->unlock();

    release();

    return m_unlocker->unlock();
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

//    QTimer::singleShot(m_config->blockTimeout() * 1000 * 60, this, [&](){
    QTimer::singleShot(.1 * 1000 * 60, this, [&]{
        unblock();
    });

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
    m_screen->installEventFilter(this);

}

void Mere::Lock::ScreenLocker::release()
{
    m_screen->releaseMouse();
    m_screen->releaseKeyboard();
    m_screen->removeEventFilter(this);
}

int Mere::Lock::ScreenLocker::ask()
{
    int ok = 0;

    Mere::Lock::LockPrompt prompt(m_screen);

    QEventLoop loop;
    connect(&prompt, &Mere::Lock::LockPrompt::entered, [&](){
        m_config->password(prompt.input());
        loop.quit();

    });
    connect(&prompt, &Mere::Lock::LockPrompt::escaped, [&](){
        ok = 1;
        loop.quit();
    });

    prompt.prompt();
    loop.exec();

    return ok;
}

bool Mere::Lock::ScreenLocker::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() == QEvent::KeyPress || event->type() == QEvent::MouseMove)
         && m_unlocker->state() != Mere::Lock::Unlocker::InProgress )
    {
#ifdef QT_DEBUG
        // - test code
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            ::exit(0);
        // - end of test code
#endif
        if (m_unlocker->attempt() < m_config->unlockAttempts())
        {
            release();
            int ok = unlock();
            capture();

            switch (ok)
            {
                case 1:
                    restore();
                    break;
                case 2:
                    block();
                    break;
                default:
                    emit unlocked();
                    break;
            }
        }

        return true;
    }

    return false;
}
