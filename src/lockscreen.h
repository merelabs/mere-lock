#ifndef MERE_LOCK_LOCKSCREEN_H
#define MERE_LOCK_LOCKSCREEN_H

#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>

class LockPrompt;

class LockScreen : public QWidget
{
    Q_OBJECT
public:
    ~LockScreen();
    explicit LockScreen(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void prompt();
    void setMessage();
    void setBackground();
    void setScreenLogo();

signals:
    void verified();

private:
    LockPrompt *m_prompt = nullptr;
};

#endif // MERE_LOCK_LOCKSCREEN_H
