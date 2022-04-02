#include "screenlocker.h"
#include "lockscreen.h"
#include "lockprompt.h"

#include <QApplication>
#include <QDesktopWidget>
Mere::Lock::ScreenLocker::~ScreenLocker()
{
    for(auto *screen : m_screens)
        delete screen;
}

Mere::Lock::ScreenLocker::ScreenLocker(QObject *parent)
    : QObject(parent),
      m_prompt(nullptr)
{
    int screenNumber = 0;
    for(QScreen *screen : QApplication::screens())
    {
        auto *lockScreen = new Mere::Lock::LockScreen(screen);
        lockScreen->installEventFilter(this);
        connect(lockScreen, &Mere::Lock::LockScreen::verified, this, [&](){
            emit verified();
        });
        if (screen == QApplication::screenAt(QCursor::pos()))
            screenNumber = m_screens.size();

        m_screens.push_back(lockScreen);
    }

    m_screen = m_screens.at(screenNumber);
}

int Mere::Lock::ScreenLocker::lock()
{

    for(auto *screen : m_screens)
        screen->lock();

    m_screen->setFocusPolicy(Qt::StrongFocus);
    m_screen->setFocus(Qt::ActiveWindowFocusReason);

    capture();

    emit locked();

    return 0;
}

int Mere::Lock::ScreenLocker::unlock()
{
    for(auto *screen : m_screens)
        screen->unlock();

    release();

    emit unlocked();

    return 0;
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


void Mere::Lock::ScreenLocker::prompt()
{
    if (!m_prompt)
    {
        m_prompt = new Mere::Lock::LockPrompt(m_screen);
        connect(m_prompt, &Mere::Lock::LockPrompt::opened, [&](){
            hideTextPrompt();
        });
        connect(m_prompt, &Mere::Lock::LockPrompt::closed, [&](){
            showTextPrompt();
        });

        connect(m_prompt, &Mere::Lock::LockPrompt::keyboardReleased, [&](){
            capture();
        });

        connect(m_prompt, &Mere::Lock::LockPrompt::verified, [&](){
            release();
            emit verified();
        });
    }

    m_prompt->showNormal();
}

void Mere::Lock::ScreenLocker::hideTextPrompt()
{
    for(auto *screen : m_screens)
        screen->hideMessage();
}

void Mere::Lock::ScreenLocker::showTextPrompt()
{
    for(auto *screen : m_screens)
        screen->showMessage();
}

bool Mere::Lock::ScreenLocker::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::MouseMove)
    {
#ifdef QT_DEBUG
        // - test code
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            ::exit(0);
        // - end of test code
#endif

        prompt();

        return true;
    }

    return false;
}

