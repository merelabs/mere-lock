#include "prompttimeout.h"
#include "config.h"
#include "ticker.h"

#include <iostream>
#include <QtMath>
#include <QPropertyAnimation>
Mere::Lock::PromptTimeout::PromptTimeout(QWidget *parent)
    : QWidget(parent)
//      m_animation(new QPropertyAnimation(this, "geometry", this)),
//      m_ticker(new Mere::Lock::Ticker(1, this)),
//      m_config(Mere::Lock::Config::instance())
{
    setGeometry(QRect(10, 10, 110, 12));
    setStyleSheet("background:red;");
qDebug() << ">>>>" << this->parent();
//    setObjectName("PromptTimeout");

//    initUI();

//    m_step = qCeil(parent->geometry().width() / m_config->unlockScreenPromptTimeout());

//    m_animation->setDuration(m_config->unlockScreenPromptTimeout() * 1000);
//    m_animation->setStartValue(QRect(0, 0, 0, 2));
//    m_animation->setEndValue(QRect(0, 0, parent->geometry().width(), 2));

//    connect(m_ticker, &Mere::Lock::Ticker::tick, this, [&](){
//        std::cout << "you can progress! :)" << std::endl;
//        progress();
//    });
}

void Mere::Lock::PromptTimeout::initUI()
{
//    setGeometry(10, 10, 110, 12);
//    setStyleSheet("background: red;");
//    setGeometry(QRect(0, 10, 100, 20));
//    setStyleSheet("backgriund:red;");
}

int Mere::Lock::PromptTimeout::start()
{
//    m_ticker->start();
//    m_animation->start();
//qDebug() << "Start PROGRESS!";

    return 0;
}

int Mere::Lock::PromptTimeout::stop()
{
////    m_ticker->stop();
//    m_animation->stop();

//    qDebug() << "Stop PROGRESS!";
//    initUI();

    return 0;
}

int Mere::Lock::PromptTimeout::progress()
{

    return 0;
}
