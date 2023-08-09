#ifndef MERE_LOCK_SCREENUNLOCKER_H
#define MERE_LOCK_SCREENUNLOCKER_H

#include "unlocker.h"

#include <iostream>

namespace Mere
{
namespace Lock
{

class Config;
class LockScreen;

class ScreenUnlocker : public Unlocker
{
    Q_OBJECT
public:
    virtual ~ScreenUnlocker();
    explicit ScreenUnlocker(LockScreen *screen, QObject *parent = nullptr);
    int unlock() override;

    void screen(LockScreen *screen);

private:
    int ask();

private:
    LockScreen *m_screen;
    Mere::Lock::Config *m_config;
};

}
}

#endif // MERE_LOCK_SCREENUNLOCKER_H
