#include "timebar.h"
#include "config.h"

#include <iostream>
#include <QPropertyAnimation>

// 0 width works like hidden bar
static const QRect TIMEBAR_INIT_RECT = QRect(10, 10, 0, 2);

Mere::Lock::Timebar::~Timebar()
{
}

Mere::Lock::Timebar::Timebar(QWidget *parent)
    : QWidget(parent),
      m_animation(new QPropertyAnimation(this, "geometry", this)),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("Timebar");
    setAttribute(Qt::WA_StyledBackground);
    setGeometry(TIMEBAR_INIT_RECT);

    m_animation->setDuration(m_config->promptTimeout() * 1000);
    m_animation->setStartValue(QRect(TIMEBAR_INIT_RECT));
    m_animation->setEndValue(QRect(TIMEBAR_INIT_RECT.x(), TIMEBAR_INIT_RECT.y(), parent->geometry().width() - 2 * TIMEBAR_INIT_RECT.x(), 2));

    connect(m_animation, &QPropertyAnimation::finished, this, [&](){
        setGeometry(TIMEBAR_INIT_RECT);
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
    setGeometry(TIMEBAR_INIT_RECT);
    return 0;
}
