#ifndef LOCKER_H
#define LOCKER_H

#include <QObject>

class LockScreen;

namespace Mere
{
namespace Lock
{

class Locker : public QObject
{
    Q_OBJECT
public:
    ~Locker();
    explicit Locker(QObject *parent = nullptr);

    int lock();
    int unlock();

signals:
    void unlocked();

private:
    LockScreen *m_screen = nullptr;
};

}
}

#endif // LOCKER_H
