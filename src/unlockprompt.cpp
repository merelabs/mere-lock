#include "unlockprompt.h"
#include "lockscreen.h"
#include "prompt.h"

Mere::Lock::UnlockPrompt::UnlockPrompt(LockScreen *screen, QObject *parent)
    : QObject(parent),
      m_screen(screen),
      m_prompt(nullptr)
{

}

std::string Mere::Lock::UnlockPrompt::input() const
{
    return m_prompt->input();
}

void Mere::Lock::UnlockPrompt::close()
{
    m_prompt->close();
}

void Mere::Lock::UnlockPrompt::prompt()
{
    if (!m_prompt)
    {
        m_prompt = new Mere::Lock::Prompt(m_screen);
        connect(m_prompt, &Mere::Lock::Prompt::attempted, [&](){
            emit attempted();
        });
        connect(m_prompt, &Mere::Lock::Prompt::cancelled, [&](){
            emit cancelled();
        });
    }

    m_prompt->showNormal();
}
