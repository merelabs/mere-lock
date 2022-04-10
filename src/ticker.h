#ifndef LOCKCOUNTER_H
#define LOCKCOUNTER_H

#include <QTimer>
#include <QDebug>
#include <QObject>

namespace Mere
{
namespace Lock
{

class Ticker : public QObject
{
    Q_OBJECT
public:
    virtual ~Ticker();
    explicit Ticker(int step, QObject *parent = nullptr);
    int start();
    int stop();

signals:
    void tick();

private:
    int m_tick;
    QTimer *m_timer;
};

}
}
#endif // LOCKCOUNTER_H
