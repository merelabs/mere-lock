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
    return ask();
}

int Mere::Lock::ScreenUnlocker::ask()
{
    int ok = 0;

    QEventLoop loop;
    Mere::Lock::UnlockPrompt prompt(m_screen);
    connect(&prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
        qint64 start =  QDateTime::currentDateTime().currentMSecsSinceEpoch();
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
        qDebug() << "TIME!" << (QDateTime::currentDateTime().currentMSecsSinceEpoch() - start);
    });
    connect(&prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
        ok = 1;
        loop.quit();
    });

    prompt.prompt();
    loop.exec();

    return ok;
}
