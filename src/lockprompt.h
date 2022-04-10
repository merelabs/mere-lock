#ifndef LOCKPROMPT_H
#define LOCKPROMPT_H

#include "prompt.h"

namespace Mere
{
namespace Lock
{

class LockPrompt : public Prompt
{
    Q_OBJECT
public:
    explicit LockPrompt(QWidget *parent = nullptr);

signals:

};

}
}
#endif // LOCKPROMPT_H
