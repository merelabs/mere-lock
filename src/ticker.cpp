#include "ticker.h"

#include <iostream>

#include <QTimer>
Mere::Lock::Ticker::~Ticker()
{
    if (m_timer)
    {
        delete m_timer;
        m_timer = nullptr;
    }
}

Mere::Lock::Ticker::Ticker(unsigned int step, QObject *parent)
    : QObject(parent),
      m_timer(new QTimer(this))
{
    m_timer->setInterval(step * 1000);
    connect(m_timer, &QTimer::timeout, this, [&](){
        std::cout << "..." << std::endl;
        emit tick();
    });
}

int Mere::Lock::Ticker::start()
{
    std::cout << "Ticker start:" << std::endl;
    m_timer->start();

    return 0;
}

int Mere::Lock::Ticker::stop()
{
    std::cout << "Ticker stop:" << std::endl;

    m_timer->stop();
    return 0;
}

int Mere::Lock::Ticker::reset(int step)
{
    std::cout << "Ticker reset:" << std::endl;

    m_timer->start(step);

    return 0;
}

