#include "locker.h"
#include "screenlocker.h"

Mere::Lock::Locker::~Locker()
{
    if (m_locker)
    {
        m_locker->disconnect();
        delete m_locker;
        m_locker = nullptr;
    }
}

Mere::Lock::Locker::Locker(QObject *parent)
    : QObject(parent)
{
    m_locker = new Mere::Lock::ScreenLocker(this);
    connect(m_locker, &Mere::Lock::ScreenLocker::unlocked, this, &Mere::Lock::Locker::unlocked);
}

int Mere::Lock::Locker::lock()
{
//    if (m_locker->isLocked())
//        return 1;

    return m_locker->lock();
}

int Mere::Lock::Locker::unlock()
{
//    if (!m_locker->isLocked())
//        return 1;
    return m_locker->unlock();
}
