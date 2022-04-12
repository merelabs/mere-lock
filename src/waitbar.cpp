#include "waitbar.h"
#include "config.h"

#include <iostream>
#include <QPropertyAnimation>

static const QRect WAITBAR_INIT_STATE = QRect(10, 10, 0, 2);

Mere::Lock::Waitbar::~Waitbar()
{
    if (m_animation)
    {
        delete m_animation;
        m_animation = nullptr;
    }
}

Mere::Lock::Waitbar::Waitbar(QWidget *parent)
    : QWidget(parent),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("PromptTimeout");
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background: red;");
    setGeometry(WAITBAR_INIT_STATE);

    m_animation = new QPropertyAnimation(this, "geometry");
    m_animation->setDuration(m_config->unlockScreenPromptTimeout() * 1000);
    m_animation->setStartValue(QRect(WAITBAR_INIT_STATE));
    m_animation->setEndValue(QRect(WAITBAR_INIT_STATE.x(), WAITBAR_INIT_STATE.y(), parent->geometry().width() - 2 * WAITBAR_INIT_STATE.x(), 2));

    connect(m_animation, &QPropertyAnimation::finished, this, [&](){
        setGeometry(WAITBAR_INIT_STATE);
        emit timeout();
    });
}

int Mere::Lock::Waitbar::start()
{
    m_animation->start();

    return 0;
}

int Mere::Lock::Waitbar::stop()
{
    m_animation->stop();

    return 0;
}

int Mere::Lock::Waitbar::reset()
{
    stop();
    setGeometry(WAITBAR_INIT_STATE);
    return 0;
}
