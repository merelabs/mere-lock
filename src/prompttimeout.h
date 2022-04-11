#ifndef MERE_LOCK_PROMPTTIMEOUT_H
#define MERE_LOCK_PROMPTTIMEOUT_H

#include <QWidget>

class QPropertyAnimation;

namespace Mere
{
namespace Lock
{

class Config;
class Ticker;

class PromptTimeout : public QWidget
{
    Q_OBJECT
public:
    explicit PromptTimeout(QWidget *parent = nullptr);

    int start();
    int stop();

private:
    void initUI();

    int progress();

signals:
    void timeout();

private:
//    unsigned int m_step;
    QPropertyAnimation *m_animation;

//    Mere::Lock::Ticker *m_ticker;
    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_PROMPTTIMEOUT_H
