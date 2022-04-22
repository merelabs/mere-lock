#include "lockprompt.h"
#include "lockscreen.h"
#include "config.h"
#include "prompt.h"

#include <iostream>

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
      m_prompt(new Prompt(screen)),
      m_config(Mere::Lock::Config::instance())
{
    connect(m_prompt, &Mere::Lock::Prompt::entered, this, &Mere::Lock::LockPrompt::attempted);
    connect(m_prompt, &Mere::Lock::Prompt::escaped, this, &Mere::Lock::LockPrompt::cancelled);

    initUI();
}

void Mere::Lock::LockPrompt::initUI()
{
    setBackground();
    setPromptLogo();

    m_prompt->prompt(Mere::Lock::LockPrompt::tr("LockPrompt").toStdString());
}

void Mere::Lock::LockPrompt::setBackground()
{
    QPalette pal = m_prompt->palette();
    QPixmap pixmap = m_config->lockScreenPromptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_prompt->size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->lockScreenPromptBackgroundColor();
        pal.setColor(QPalette::Window, QColor(color));
    }

    m_prompt->setPalette(pal);
}

void Mere::Lock::LockPrompt::setPromptLogo()
{
    if(!m_config->lockScreenPromptLogoShow()) return;
    m_prompt->setLogo(m_config->lockScreenPromptLogo());
}


void Mere::Lock::LockPrompt::prompt() const
{
    m_prompt->showNormal();
}

std::string Mere::Lock::LockPrompt::input() const
{
    return m_prompt->input();
}
