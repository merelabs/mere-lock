#include "ticker.h"

Mere::Lock::Ticker::~Ticker()
{
    if (m_timer)
    {
        delete m_timer;
        m_timer = nullptr;
    }
}

Mere::Lock::Ticker::Ticker(int step, QObject *parent)
    : QObject(parent),
      m_timer(new QTimer(this))
{
    m_timer->setInterval(std::abs(step) * 1000);
    connect(m_timer, &QTimer::timeout, this, [=](){
        emit tick();
    });
}

int Mere::Lock::Ticker::start()
{
    m_timer->start();

    return 0;
}

int Mere::Lock::Ticker::stop()
{
    return 0;
}

