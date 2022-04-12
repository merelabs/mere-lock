#ifndef MERE_LOCK_PROMPTBAR_H
#define MERE_LOCK_PROMPTBAR_H

#include <QWidget>

class QPropertyAnimation;

namespace Mere
{
namespace Lock
{

class Config;

class Waitbar : public QWidget
{
    Q_OBJECT
public:
    virtual ~Waitbar();
    explicit Waitbar(QWidget *parent = nullptr);

    int start();
    int stop();
    int reset();

signals:
    void timeout();

private:
    unsigned int m_step;
    QPropertyAnimation *m_animation;

    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_PROMPTBAR_H
