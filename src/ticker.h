#ifndef MERE_LOCK_TICKER_H
#define MERE_LOCK_TICKER_H

#include <QObject>

class QTimer;

namespace Mere
{
namespace Lock
{

class Ticker : public QObject
{
    Q_OBJECT
public:
    virtual ~Ticker();
    explicit Ticker(unsigned int step, QObject *parent = nullptr);

    int start();
    int stop();

    int reset(int step = 0);

signals:
    void tick();

private:
    int m_tick;
    QTimer *m_timer;
};

}
}
#endif // MERE_LOCK_TICKER_H
