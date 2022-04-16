#include "screenunlocker.h"
#include "config.h"
#include "lockscreen.h"
#include "prompt.h"
#include "unlockprompt.h"

#include "mere/auth/service.h"
#include "mere/utils/stringutils.h"

#include <QTimer>
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
    prompt();

    return 0;
}

void Mere::Lock::ScreenUnlocker::prompt()
{
    if (!m_prompt)
    {
        m_prompt = new Mere::Lock::UnlockPrompt(m_screen, this);
        connect(m_prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
            verify(m_prompt->input());
        });
        connect(m_prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
            state(0);
            m_prompt->close();
            emit cancelled();
        });
    }
    m_prompt->prompt();
}

bool Mere::Lock::ScreenUnlocker::verify(const std::string &secret)
{
    bool ok = Mere::Lock::Unlocker::verify(secret);
    if (ok)
    {
        state(0);
        m_prompt->close();
        emit unlocked();
    }
    else
    {
        m_prompt->message(Mere::Lock::Prompt::tr("UnlockAttemptFailed").toStdString());

        if (attempt() == m_config->unlockAttempts())
        {
            state(0);
            m_prompt->close();
            QTimer::singleShot(m_config->blockTimeout() * 1000 * 60, this, [&](){
                attempt(0);
                emit unblocked();
            });

            emit blocked();
        }
    }

    return ok;
}
