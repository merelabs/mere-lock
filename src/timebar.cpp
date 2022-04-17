#include "timebar.h"
#include "config.h"

#include <iostream>
#include <QPropertyAnimation>

// 0 width works like hidden bar
static const QRect WAITBAR_INIT_STATE = QRect(10, 10, 0, 2);

Mere::Lock::Timebar::~Timebar()
{
}

Mere::Lock::Timebar::Timebar(QWidget *parent)
    : QWidget(parent),
      m_animation(new QPropertyAnimation(this, "geometry", this)),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("WaitBar");
    setAttribute(Qt::WA_StyledBackground);
    setGeometry(WAITBAR_INIT_STATE);

    m_animation->setDuration(m_config->unlockScreenPromptTimeout() * 1000);
    m_animation->setStartValue(QRect(WAITBAR_INIT_STATE));
    m_animation->setEndValue(QRect(WAITBAR_INIT_STATE.x(), WAITBAR_INIT_STATE.y(), parent->geometry().width() - 2 * WAITBAR_INIT_STATE.x(), 2));

    connect(m_animation, &QPropertyAnimation::finished, this, [&](){
        setGeometry(WAITBAR_INIT_STATE);
        emit timeout();
    });
}

int Mere::Lock::Timebar::start()
{
    qDebug() << "Waitbar::start";
    m_animation->start();

    return 0;
}

int Mere::Lock::Timebar::stop()
{
    qDebug() << "Waitbar::stop";
    m_animation->stop();

    return 0;
}

int Mere::Lock::Timebar::reset()
{
    qDebug() << "Waitbar::reset";
    stop();
    setGeometry(WAITBAR_INIT_STATE);
    return 0;
}
