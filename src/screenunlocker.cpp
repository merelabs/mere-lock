#include "screenunlocker.h"
#include "config.h"
#include "lockscreen.h"
#include "unlockprompt.h"

#include <QEventLoop>

Mere::Lock::ScreenUnlocker::~ScreenUnlocker()
{
}

Mere::Lock::ScreenUnlocker::ScreenUnlocker(LockScreen *screen, QObject *parent)
    : Unlocker(parent),
      m_screen(screen),
      m_config(Mere::Lock::Config::instance())
{

}

void Mere::Lock::ScreenUnlocker::screen(LockScreen *screen)
{
    m_screen = screen;
    emit cancelled();
}

int Mere::Lock::ScreenUnlocker::unlock()
{
    return ask();
}

int Mere::Lock::ScreenUnlocker::ask()
{
    if (!m_screen) return 1;

    int ok = 0;

    QEventLoop loop;
    Mere::Lock::UnlockPrompt prompt(m_screen);
    connect(&prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
        if(verify(prompt.input()))
        {
            attempt(0);
            loop.quit();
        }
        else if(attempt() == m_config->unlockAttempts())
        {
            attempt(0);
            ok = 2;
            loop.quit();
        }
        else
        {
            prompt.failed();
        }
    });
    connect(&prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
        ok = 1;
        loop.quit();
    });

    prompt.prompt();

    // primary screen is removed when prompt is visible, need to close it forcefully!
    connect(this, &Mere::Lock::ScreenUnlocker::cancelled, [&](){
        ok = 1;
        loop.quit();
    });
    loop.exec();

    disconnect();

    return ok;
}
