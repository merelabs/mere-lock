#ifndef LOCKVIEW_H
#define LOCKVIEW_H

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
    void moveToCenterScreen();

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

#endif // LOCKVIEW_H
