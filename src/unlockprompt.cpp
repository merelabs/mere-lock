#include "unlockprompt.h"
#include "lockscreen.h"
#include "prompt.h"

Mere::Lock::UnlockPrompt::~UnlockPrompt()
{
    if(m_prompt)
    {
        delete m_prompt;
        m_prompt = nullptr;
    }
}

Mere::Lock::UnlockPrompt::UnlockPrompt(LockScreen *screen, QObject *parent)
    : QObject(parent),
      m_prompt(new Mere::Lock::Prompt(screen))
{
    connect(m_prompt, &Mere::Lock::Prompt::attempted, [&](){
        emit attempted();
    });
    connect(m_prompt, &Mere::Lock::Prompt::cancelled, [&](){
        emit cancelled();
    });
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
    m_prompt->showNormal();
}
