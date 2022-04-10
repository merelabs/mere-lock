#include "screenunlocker.h"
#include "config.h"
#include "lockscreen.h"
#include "prompt.h"

#include "mere/auth/service.h"

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
        m_prompt = new Mere::Lock::Prompt(m_screen);
        connect(m_prompt, &Mere::Lock::Prompt::attempted, [&](){
            bool ok = verify();
            if (ok)
            {
                state(0);
                m_prompt->close();
                emit unlocked();
            }
            else
            {
                int _attempt = attempt();
                ++_attempt;
                attempt(_attempt);

                if (attempt() == m_config->attempts())
                {
                    state(0);
                    m_prompt->close();
                    QTimer::singleShot(m_config->blocktime() * 1000 * 60, this, [&](){
                        attempt(0);
                    });
                    emit blocked();
                }
            }
        });
        connect(m_prompt, &Mere::Lock::Prompt::cancelled, [&](){
            state(0);
            m_prompt->close();
            emit cancelled();
        });
    }

    state(1);
    m_prompt->showNormal();
}

bool Mere::Lock::ScreenUnlocker::verify()
{
    std::string input = m_prompt->input();

    std::string password = m_config->password();
    if (!password.empty())
        return (password.compare(input) == 0);

    Mere::Auth::Service service;
    return service.verify(input);
}
