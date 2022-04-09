#ifndef SCREENUNLOCKER_H
#define SCREENUNLOCKER_H

#include "unlocker.h"

#include <iostream>

namespace Mere
{
namespace Lock
{

class LockPrompt;
class LockScreen;
class Config;

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
    Mere::Lock::LockPrompt *m_prompt;

    Mere::Lock::Config *m_config;
};

}
}

#endif // SCREENUNLOCKER_H
