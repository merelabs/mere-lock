#ifndef LOCKPROMPT_H
#define LOCKPROMPT_H

#include "prompt.h"
#include <QObject>

namespace Mere
{
namespace Lock
{

class Config;
//class Prompt;
class LockScreen;

class LockPrompt : public Prompt
{
    Q_OBJECT
public:
    virtual ~LockPrompt();
    explicit LockPrompt(LockScreen *screen, QWidget *parent = nullptr);
//    void close();
    void prompt();

//    std::string input() const;
//    void message(const std::string &message);

private:
    void setBackground() override;
    void setPromptLogo() override;

signals:
    void attempted();
    void cancelled();

private:
//    Prompt *m_prompt;
    Mere::Lock::Config *m_config;

};

}
}
#endif // LOCKPROMPT_H
