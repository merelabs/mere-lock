#include "screenunlocker.h"
#include "config.h"
#include "lockscreen.h"
#include "unlockprompt.h"

#include "mere/auth/service.h"
#include "mere/utils/stringutils.h"

#include <QTimer>

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
        m_prompt = new Mere::Lock::UnlockPrompt(m_screen);
        connect(m_prompt, &Mere::Lock::UnlockPrompt::attempted, [&](){
            bool ok = verify();
            if (ok)
            {
                state(0);
                m_prompt->close();
                emit unlocked();
            }
            else
            {
                attempt(attempt() + 1);
                if (attempt() == m_config->unlockAttempts())
                {
                    state(0);
                    m_prompt->close();
                    QTimer::singleShot(.1 * 1000 * 60, this, [&](){
                        attempt(0);
                        emit unblocked();
                    });

                    emit blocked();
                }
            }
        });
        connect(m_prompt, &Mere::Lock::UnlockPrompt::cancelled, [&](){
            state(0);
            m_prompt->close();
            emit cancelled();
        });

    }

    state(1);
    m_prompt->prompt();
}

bool Mere::Lock::ScreenUnlocker::verify()
{
    std::string input = m_prompt->input();
    if (Mere::Utils::StringUtils::isBlank(input))
        return false;

    std::string password = m_config->password();
    if (Mere::Utils::StringUtils::isBlank(password))
        return false;

    if (input == password)
        return true;

    Mere::Auth::Service service;
    return service.verify(input);
}

