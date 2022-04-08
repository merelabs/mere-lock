#ifndef SCREELOCKER_H
#define SCREELOCKER_H

#include <QObject>
#include <QDebug>
#include <QEvent>

namespace Mere
{
namespace Lock
{

class LockScreen;
class LockPrompt;
class Unlocker;

class ScreenLocker : public QObject
{
    Q_OBJECT
public:
    ~ScreenLocker();
    explicit ScreenLocker(QObject *parent = nullptr);

    int lock();
    int unlock();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void capture();
    void release();

    void hideTextPrompt();
    void showTextPrompt();

signals:
    void locked();
    void unlocked();

private:
    Mere::Lock::Unlocker *m_unlocker;
    Mere::Lock::LockScreen *m_screen;
    std::vector<Mere::Lock::LockScreen *> m_screens;
};

}
}
#endif // SCREELOCKER_H
