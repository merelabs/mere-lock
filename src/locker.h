#ifndef LOCKER_H
#define LOCKER_H

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

signals:
    void locked();
    void unlocked();

private:
    ScreenLocker *m_locker;
};

}
}

#endif // LOCKER_H
