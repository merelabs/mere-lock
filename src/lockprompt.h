#ifndef LOCKPROMPT_H
#define LOCKPROMPT_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class Prompt;
class LockScreen;

class LockPrompt : public QObject
{
    Q_OBJECT
public:
    virtual ~LockPrompt();
    explicit LockPrompt(LockScreen *screen, QObject *parent = nullptr);
    void close();
    void prompt();

    std::string input() const;
    void message(const std::string &message);

signals:
    void attempted();
    void cancelled();

private:
    Prompt *m_prompt;
};

}
}
#endif // LOCKPROMPT_H
