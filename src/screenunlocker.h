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
class Prompt;

class ScreenUnlocker : public Unlocker
{
    Q_OBJECT
public:
    explicit ScreenUnlocker(LockScreen *screen, QObject *parent = nullptr);
    int unlock() override;

private:
    void prompt();
    bool verify();    

private:
    Mere::Lock::LockScreen *m_screen;
    Mere::Lock::Prompt *m_prompt;

    Mere::Lock::Config *m_config;
};

}
}

#endif // MERE_LOCK_SCREENUNLOCKER_H
