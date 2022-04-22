#ifndef MERE_LOCK_LOCKPROMPT_H
#define MERE_LOCK_LOCKPROMPT_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class Config;
class Prompt;
class LockScreen;

class LockPrompt : public QObject
{
    Q_OBJECT
public:
    virtual ~LockPrompt();
    explicit LockPrompt(LockScreen *screen, QObject *parent = nullptr);

    void prompt() const;
    std::string input() const;

protected:
    void initUI();

private:
    void setBackground();
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
#endif // MERE_LOCK_LOCKPROMPT_H
