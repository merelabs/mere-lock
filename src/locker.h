#ifndef MERE_LOCK_LOCKER_H
#define MERE_LOCK_LOCKER_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class ScreenLocker;

class Locker : public QObject
{
    Q_OBJECT
public:
    ~Locker();
    explicit Locker(QObject *parent = nullptr);

    int lock();
    int unlock();

    static uint Attempts;

signals:
    void locked();
    void unlocked();

private:
    ScreenLocker *m_locker;
};

}
}

#endif // MERE_LOCK_LOCKER_H
