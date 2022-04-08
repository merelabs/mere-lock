#include "locker.h"
#include "screenlocker.h"

uint Mere::Lock::Locker::Attempts = 0;

Mere::Lock::Locker::~Locker()
{
    if (m_locker)
    {
        delete m_locker;
        m_locker = nullptr;
    }
}

Mere::Lock::Locker::Locker(QObject *parent)
    : QObject(parent)
{
    m_locker = new Mere::Lock::ScreenLocker(this);
    connect(m_locker, &Mere::Lock::ScreenLocker::unlocked, this, [&](){
        unlock();
    });
}

int Mere::Lock::Locker::lock()
{
    m_locker->lock();
    emit locked();

    return 0;
}

int Mere::Lock::Locker::unlock()
{
    m_locker->unlock();

    emit unlocked();

    return 0;
}
