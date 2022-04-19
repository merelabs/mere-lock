#include "unlockprompt.h"
#include "lockscreen.h"
#include "config.h"

#include <iostream>

Mere::Lock::UnlockPrompt::~UnlockPrompt()
{
}

Mere::Lock::UnlockPrompt::UnlockPrompt(LockScreen *screen, QWidget *parent)
    : Prompt(screen),
      m_config(Mere::Lock::Config::instance())
{
    initUI();
}

void Mere::Lock::UnlockPrompt::initUI()
{
    Mere::Lock::Prompt::initUI();
    prompt(Mere::Lock::UnlockPrompt::tr("UnlockPrompt").toStdString());
}

void Mere::Lock::UnlockPrompt::setBackground()
{
    QPalette pal = palette();
    QPixmap pixmap = m_config->unlockScreenPromptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->unlockScreenPromptBackgroundColor();
        if (color.isValid())
        {
            pal.setColor(QPalette::Window, QColor(color));
        }
    }

    setPalette(pal);
}

void Mere::Lock::UnlockPrompt::setPromptLogo()
{
    if(!m_config->unlockScreenPromptLogoShow()) return;

    Mere::Lock::Prompt::setPromptLogo();

//    QPixmap pixmap = m_config->unlockScreenPromptLogo();
//    if (pixmap.isNull())
//    {
////        std::cout << "Unable to create image for prompt logo; please check the image path." << std::endl;
//        std::cout << "Lock screen prompt logo missing!" << std::endl;
//        return;
//    }

    setLogo(m_config->unlockScreenPromptLogo());

//    QSize size(geometry().width() - 50, 96);
//    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//    QLabel *label = new QLabel(this);
//    label->setMargin(0);
//    label->setContentsMargins(0, 0, 0, 0);
//    label->setAlignment(Qt::AlignCenter);
//    label->setMinimumHeight(96);
//    label->setMaximumHeight(96);
//    label->setPixmap(pixmap);

//    label->move(this->width()/2 - label->width()/2, 30);
}
