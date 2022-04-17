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

int Mere::Lock::ScreenUnlocker::unlock()
{
    state(1);
    int ok = ask();

    state(0);

    return ok;
}

int Mere::Lock::ScreenUnlocker::ask()
{
    int ok = 0;

    Mere::Lock::UnlockPrompt prompt(m_screen);

    QEventLoop loop;
    connect(&prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
        if(verify(prompt.input()) || attempt() == m_config->unlockAttempts())
        {
            attempt(0);
            loop.quit();
        }
    });
    connect(&prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
        ok = 1;
        loop.quit();
    });

    prompt.prompt();
    loop.exec();

    return ok;
}
