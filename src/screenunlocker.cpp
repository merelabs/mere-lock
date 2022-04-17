#include "screenunlocker.h"
#include "config.h"
#include "lockscreen.h"
#include "prompt.h"
#include "unlockprompt.h"

#include "mere/auth/service.h"
#include "mere/utils/stringutils.h"

#include <QTimer>
#include <QEventLoop>

Mere::Lock::ScreenUnlocker::~ScreenUnlocker()
{
}

Mere::Lock::ScreenUnlocker::ScreenUnlocker(LockScreen *screen, QObject *parent)
    : Unlocker(parent),
      m_screen(screen),
      m_prompt(nullptr),
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
//    if (!m_prompt)
//    {
//        m_prompt = new Mere::Lock::UnlockPrompt(m_screen, this);
//        connect(m_prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
//            verify(m_prompt->input());
//        });
//        connect(m_prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
//            state(0);
//            m_prompt->close();
//            emit cancelled();
//        });
//    }
//    m_prompt->prompt();

    int ok = 0;

    Mere::Lock::UnlockPrompt prompt(m_screen);

    QEventLoop loop;
    connect(&prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
        ok = verify(prompt.input());
        if (ok == 0 || ok == 2)
            loop.quit();

    });
    connect(&prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
        ok = 1;
        loop.quit();
    });

    prompt.prompt();
    loop.exec();

    return ok;
}

int Mere::Lock::ScreenUnlocker::verify(const std::string &secret)
{
//    bool ok = Mere::Lock::Unlocker::verify(secret);
//    if (ok)
//    {
//        state(0);
//        m_prompt->close();
//        emit unlocked();
//    }
//    else
//    {
//        m_prompt->message(Mere::Lock::Prompt::tr("UnlockAttemptFailed").toStdString());

//        if (attempt() == m_config->unlockAttempts())
//        {
//            state(0);
//            m_prompt->close();
//            QTimer::singleShot(m_config->blockTimeout() * 1000 * 60, this, [&](){
//                attempt(0);
//                emit unblocked();
//            });

//            emit blocked();
//        }
//    }

//    return ok;

    int ok = Mere::Lock::Unlocker::verify(secret);
    if (ok && attempt() == m_config->unlockAttempts())
    {
        attempt(0);
        ok = 2;
    }

    return ok;
}
