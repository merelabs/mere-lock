#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H

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
    void setBackground();
    void setScreenLogo();


signals:
    void verified();

private:
    QLabel *m_label;
    LockPrompt *m_prompt = nullptr;
};

#endif // LOCKSCREEN_H
