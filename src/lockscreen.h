#ifndef MERE_LOCK_LOCKSCREEN_H
#define MERE_LOCK_LOCKSCREEN_H

#include <QTime>
#include <QLabel>
#include <QWidget>

namespace Mere
{
namespace Lock
{

class Config;

class LockScreen : public QWidget
{
    Q_OBJECT
public:
    ~LockScreen();
    explicit LockScreen(QScreen *screen, QWidget *parent = nullptr);
    void lock();
    void unlock();

    void block();
    void unblock();

    bool isBlocked() const;


    void tick();
    void restore();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setTime();
    void setTimePosition();
    void setTimeStyle(const QColor &color, const int size);
    void setTimeStyle(const QColor &color, const QFont &font);

    void setLockTimeStyle();
    void setLockTimePosition();

    void setBlockTimeStyle();
    void setBlockTimePosition();

    void setMessage();
    void setMessagePosition();
    void setMessageStyle(const QColor &color, const int size);
    void setMessageStyle(const QColor &color, const QFont &font);

    void setLockMessageStyle();
    void setLockMessagePosition();
    void setBlockMessageStyle();
    void setBlockMessagePosition();

    void setBackground();
    void setLockBackground();
    void setBlockBackground();

    void setBackground(const QVariant &background);
    void setBackground(QPixmap pixmap, QColor color);

    void setScreenLogo();

    void applyLockTheme();
    void applyBlockTheme();

    void moveToCenter(QLabel *label);
    void setTextStyle(QLabel *label, const QColor &color, const int size);
    void setTextStyle(QLabel *label, const QColor &color, const QFont &font);

private:
    QLabel *m_time;
    QLabel *m_text;

    QTime m_blocktime;
    QTime m_elaspsetime;

    QScreen *m_screen;
    Mere::Lock::Config *m_config;
};

}
}
#endif // MERE_LOCK_LOCKSCREEN_H
