#ifndef MERE_LOCK_LOCKPROMPT_H
#define MERE_LOCK_LOCKPROMPT_H

#include "prompt.h"

namespace Mere
{
namespace Lock
{

class Config;
class LockScreen;

class LockPrompt : public Prompt
{
    Q_OBJECT
public:
    virtual ~LockPrompt();
    explicit LockPrompt(LockScreen *screen, QWidget *parent = nullptr);

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
#endif // MERE_LOCK_LOCKPROMPT_H
