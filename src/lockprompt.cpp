#include "lockprompt.h"
#include "lockscreen.h"
//#include "prompt.h"
#include "config.h"

#include "mere/utils/stringutils.h"

#include <iostream>

Mere::Lock::LockPrompt::~LockPrompt()
{
//    if (m_prompt)
//    {
//        m_prompt->disconnect();
//        delete m_prompt;
//        m_prompt = nullptr;
//    }
}

Mere::Lock::LockPrompt::LockPrompt(LockScreen *screen, QWidget *parent)
    : Prompt(screen),
      m_config(Mere::Lock::Config::instance())
//      m_prompt(new Mere::Lock::Prompt(screen))
{
//    connect(this, &Mere::Lock::Prompt::entered, this, &Mere::Lock::LockPrompt::attempted);
//    connect(this, &Mere::Lock::Prompt::escaped, this, &Mere::Lock::LockPrompt::cancelled);

//    m_prompt->logo();
//    m_prompt->background();
//    m_prompt->prompt(Mere::Lock::LockPrompt::tr("LockPrompt").toStdString());
//    m_prompt->init();
}

//std::string Mere::Lock::LockPrompt::input() const
//{
//    return m_prompt->input();
//}

//void Mere::Lock::LockPrompt::message(const std::string &message)
//{
//    m_prompt->message(message);
//}

//void Mere::Lock::LockPrompt::close()
//{
//    m_prompt->close();
//}

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

    QPixmap pixmap = m_config->lockScreenPromptLogo();
    if (pixmap.isNull())
    {
//        std::cout << "Unable to create image for prompt logo; please check the image path." << std::endl;
        std::cout << "Lock screen prompt logo missing!" << std::endl;
        return;
    }

    QSize size(geometry().width() - 50, 96);
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *label = new QLabel(this);
    label->setMargin(0);
    label->setContentsMargins(0, 0, 0, 0);
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumHeight(96);
    label->setMaximumHeight(96);
    label->setPixmap(pixmap);

    label->move(this->width()/2 - label->width()/2, 30);
}

void Mere::Lock::LockPrompt::prompt()
{
//    m_prompt->showNormal();
    showNormal();
}
