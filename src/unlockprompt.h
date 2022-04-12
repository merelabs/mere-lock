#ifndef MERE_LOCK_UNLOCKPROMPT_H
#define MERE_LOCK_UNLOCKPROMPT_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class Prompt;
class LockScreen;

class UnlockPrompt : public QObject
{
    Q_OBJECT
public:
    virtual ~UnlockPrompt();
    explicit UnlockPrompt(LockScreen *screen, QObject *parent = nullptr);

    void close();
    void prompt();

    std::string input() const;

signals:
    void attempted();
    void cancelled();

private:
    Prompt *m_prompt;
};

}
}
#endif // MERE_LOCK_UNLOCKPROMPT_H
