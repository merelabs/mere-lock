#ifndef MERE_LOCK_UNLOCKPROMPT_H
#define MERE_LOCK_UNLOCKPROMPT_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class Config;
class Prompt;
class LockScreen;

class UnlockPrompt : public QObject
{
    Q_OBJECT
public:
    virtual ~UnlockPrompt();
    explicit UnlockPrompt(LockScreen *screen, QObject *parent = nullptr);

    void prompt() const;
    std::string input() const;

    void failed() const;

protected:
    void initUI();

private:
    void setBackground() ;
    void setPromptLogo();

signals:
    void attempted();
    void cancelled();

private:
    Prompt *m_prompt;
    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_UNLOCKPROMPT_H
