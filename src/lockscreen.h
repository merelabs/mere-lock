#ifndef MERE_LOCK_LOCKSCREEN_H
#define MERE_LOCK_LOCKSCREEN_H

#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>


namespace Mere
{
namespace Lock
{

class Config;
class UnlockPrompt;

class LockScreen : public QWidget
{
    Q_OBJECT
public:
    ~LockScreen();
    explicit LockScreen(QScreen *screen, QWidget *parent = nullptr);
    void lock();
    void unlock();
    void block();

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
    UnlockPrompt *m_prompt;

    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_LOCKSCREEN_H
