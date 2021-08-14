#ifndef MERE_LOCK_LOCKPROMPT_H
#define MERE_LOCK_LOCKPROMPT_H

#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QWidget>

class LockPrompt : public QWidget
{
    Q_OBJECT
public:
    ~LockPrompt();
    explicit LockPrompt(QScreen *screen, QWidget *parent = nullptr);

protected:
    void setVisible(bool visible) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    static const int timeoutCheckInterval;
    static const int timeoutStartOffset;

    void initUI();
    void setShadow();
    void setBackground();
    void setPromptLogo();
    void setTimeout();

    void initMessageUI();

signals:
    void verified();
    void keyboardGrabbed();
    void keyboardReleased();

    void closed();

private slots:
    void clear();
    void verify();

private:
//    QLabel *m_prompt;
    QLabel *m_result;
    QLineEdit *m_password;

    qint64 m_timeoutStart;
    QWidget *m_timeoutPanel;
    QTimer *m_timeoutTimer = nullptr;

    QScreen *m_screen;
};

#endif // MERE_LOCK_LOCKPROMPT_H
