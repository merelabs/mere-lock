#include "unlockprompt.h"
#include "lockscreen.h"
#include "config.h"
#include "prompt.h"

#include <iostream>

Mere::Lock::UnlockPrompt::~UnlockPrompt()
{
    if (m_prompt)
    {
        m_prompt->disconnect();
        delete m_prompt;
        m_prompt = nullptr;
    }
}

Mere::Lock::UnlockPrompt::UnlockPrompt(LockScreen *screen, QObject *parent)
    : QObject(screen),
      m_prompt(new Prompt(screen)),
      m_config(Mere::Lock::Config::instance())
{
    connect(m_prompt, &Mere::Lock::Prompt::entered, this, &Mere::Lock::UnlockPrompt::attempted);
    connect(m_prompt, &Mere::Lock::Prompt::escaped, this, &Mere::Lock::UnlockPrompt::cancelled);

    initUI();
}

void Mere::Lock::UnlockPrompt::initUI()
{
    setBackground();
    setPromptLogo();

    m_prompt->prompt(Mere::Lock::UnlockPrompt::tr("UnlockPrompt").toStdString());
}

void Mere::Lock::UnlockPrompt::setBackground()
{
    QPalette pal = m_prompt->palette();
    QPixmap pixmap = m_config->unlockScreenPromptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_prompt->size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->unlockScreenPromptBackgroundColor();
        pal.setColor(QPalette::Window, QColor(color));
    }

    m_prompt->setPalette(pal);
}

void Mere::Lock::UnlockPrompt::setPromptLogo()
{
    if(!m_config->unlockScreenPromptLogoShow()) return;

    m_prompt->setLogo(m_config->unlockScreenPromptLogo());
}

void Mere::Lock::UnlockPrompt::prompt() const
{
    m_prompt->showNormal();
}

std::string Mere::Lock::UnlockPrompt::input() const
{
    return m_prompt->input();
}

void Mere::Lock::UnlockPrompt::failed() const
{
    m_prompt->message(Mere::Lock::UnlockPrompt::tr("UnlockAttemptFailed").toStdString());
}
