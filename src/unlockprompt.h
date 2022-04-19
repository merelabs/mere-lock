#ifndef MERE_LOCK_UNLOCKPROMPT_H
#define MERE_LOCK_UNLOCKPROMPT_H

#include "prompt.h"

namespace Mere
{
namespace Lock
{

class Config;
class LockScreen;

class UnlockPrompt : public Prompt
{
    Q_OBJECT
public:
    virtual ~UnlockPrompt();
    explicit UnlockPrompt(LockScreen *screen, QWidget *parent = nullptr);

protected:
    void initUI() override;

private:
    void setBackground() override;
    void setPromptLogo() override;

signals:
    void attempted();
    void cancelled();

private:
    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_UNLOCKPROMPT_H
