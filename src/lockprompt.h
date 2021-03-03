#ifndef MERE_LOCK_LOCKPROMPT_H
#define MERE_LOCK_LOCKPROMPT_H

#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QWidget>

class LockPrompt : public QWidget
{
    Q_OBJECT
public:
    ~LockPrompt();
    explicit LockPrompt(QWidget *parent = nullptr);

    void initUI();

    QString password() const;

protected:
    void setVisible(bool visible) override;
    void keyReleaseEvent(QKeyEvent *keyEvent) override;

private:
    void setShadow();
    void setBackground();
    void setPromptLogo();

signals:
    void verified();
    void keyboardGrabbed();
    void keyboardReleased();

private slots:
    void clear();
    void verify();

private:
    QLabel *m_prompt;
    QLabel *m_result;
    QLineEdit *m_password;
};

#endif // MERE_LOCK_LOCKPROMPT_H
