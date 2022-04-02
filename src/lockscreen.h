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

class LockPrompt;

class LockScreen : public QWidget
{
    Q_OBJECT
public:
    ~LockScreen();
    explicit LockScreen(QScreen *screen, QWidget *parent = nullptr);
    void lock();
    void unlock();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void prompt();
    void setMessage();
    void setBackground();
    void setScreenLogo();

    void hideMessage();
    void showMessage();

signals:
    void verified();

private:
    QScreen *m_screen;
    LockPrompt *m_prompt;
};

}
}
#endif // MERE_LOCK_LOCKSCREEN_H
