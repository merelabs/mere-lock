#include "lockprompt.h"
#include "lockscreen.h"
#include "prompt.h"

Mere::Lock::LockPrompt::~LockPrompt()
{
    if (m_prompt)
    {
        m_prompt->disconnect();
        delete m_prompt;
        m_prompt = nullptr;
    }
}

Mere::Lock::LockPrompt::LockPrompt(LockScreen *screen, QObject *parent)
    : QObject(parent),
      m_prompt(new Mere::Lock::Prompt(screen))
{
    connect(m_prompt, &Mere::Lock::Prompt::entered, this, [&](){
        emit attempted();
    });
    connect(m_prompt, &Mere::Lock::Prompt::escaped, [&](){
        emit cancelled();
    });

    m_prompt->prompt(Mere::Lock::LockPrompt::tr("LockPrompt").toStdString());
}

std::string Mere::Lock::LockPrompt::input() const
{
    return m_prompt->input();
}

void Mere::Lock::LockPrompt::message(const std::string &message)
{
    m_prompt->message(message);
}

void Mere::Lock::LockPrompt::close()
{
    m_prompt->close();
}

void Mere::Lock::LockPrompt::prompt()
{
    m_prompt->showNormal();
}
