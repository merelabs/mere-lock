#ifndef UNLOCKPROMPT_H
#define UNLOCKPROMPT_H

#include "prompt.h"

namespace Mere
{
namespace Lock
{

class UnlockPrompt : public Prompt
{
    Q_OBJECT
public:
    explicit UnlockPrompt(QWidget *parent = nullptr);

private:
    void initUI();

signals:
private:
};

}
}
#endif // UNLOCKPROMPT_H
