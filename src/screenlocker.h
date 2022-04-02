#ifndef SCREELOCKER_H
#define SCREELOCKER_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class LockScreen;

class ScreenLocker : public QObject
{
    Q_OBJECT
public:
    ~ScreenLocker();
    explicit ScreenLocker(QObject *parent = nullptr);

    int lock();
    int unlock();

signals:
    void locked();
    void unlocked();
    void verified();

private:
    std::vector<Mere::Lock::LockScreen *> m_screens;
};

}
}
#endif // SCREELOCKER_H
