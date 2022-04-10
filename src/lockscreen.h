#ifndef MERE_LOCK_LOCKSCREEN_H
#define MERE_LOCK_LOCKSCREEN_H

#include <QTime>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>

namespace Mere
{
namespace Lock
{

class Config;
class Prompt;

class LockScreen : public QWidget
{
    Q_OBJECT
public:
    ~LockScreen();
    explicit LockScreen(QScreen *screen, QWidget *parent = nullptr);
    void lock();
    void unlock();
    void block();

    void tick();

    void hideMessage();
    void showMessage();

private:
    void setTime();
    void setMessage();
    void setBackground();
    void setScreenLogo();

signals:
    void verified();

private:
    QLabel *m_time;
    QLabel *m_text;
    QScreen *m_screen;
    Prompt *m_prompt;

    QTime m_timer;
    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_LOCKSCREEN_H
