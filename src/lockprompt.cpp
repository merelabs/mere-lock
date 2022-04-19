#include "lockprompt.h"
#include "lockscreen.h"
#include "config.h"

#include <iostream>

Mere::Lock::LockPrompt::~LockPrompt()
{
}

Mere::Lock::LockPrompt::LockPrompt(LockScreen *screen, QWidget *parent)
    : Prompt(screen),
      m_config(Mere::Lock::Config::instance())
{
    initUI();
}

void Mere::Lock::LockPrompt::initUI()
{
    Mere::Lock::Prompt::initUI();
    prompt(Mere::Lock::LockPrompt::tr("LockPrompt").toStdString());
}

void Mere::Lock::LockPrompt::setBackground()
{
    QPalette pal = palette();
    QPixmap pixmap = m_config->lockScreenPromptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->lockScreenPromptBackgroundColor();
        if (color.isValid())
        {
            pal.setColor(QPalette::Window, QColor(color));
        }
    }

    setPalette(pal);
}

void Mere::Lock::LockPrompt::setPromptLogo()
{
    if(!m_config->lockScreenPromptLogoShow()) return;
    Mere::Lock::Prompt::setPromptLogo();
    setLogo(m_config->lockScreenPromptLogo());
}
