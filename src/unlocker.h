#ifndef UNLOCKER_H
#define UNLOCKER_H

#include <QObject>

namespace Mere
{
namespace Lock
{

class Unlocker : public QObject
{
    Q_OBJECT
public:
    explicit Unlocker(QObject *parent = nullptr);
    virtual int unlock()= 0;
    virtual int state();
    virtual void state(unsigned int state);

    virtual unsigned int attempt();
    virtual void attempt(unsigned int attempt);

    static int InProgress;

signals:
    void blocked();
    void unlocked();
    void attempted();
    void cancelled();

private:
    unsigned int m_state;
    unsigned int m_attempt;
};

}
}
#endif // UNLOCKER_H
