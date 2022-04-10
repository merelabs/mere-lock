#include "lockscreen.h"
#include "config.h"

#include <iostream>

#include <QScreen>
#include <QWindow>
#include <QApplication>

Mere::Lock::LockScreen::~LockScreen()
{
}

Mere::Lock::LockScreen::LockScreen(QScreen *screen, QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint),
      m_blocktime(-1, -1),
      m_elaspsetime(0, 0),
      m_screen(screen),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("LockScreen-" + screen->name());

//    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

    setTime();
    setMessage();
    setBackground();
    setScreenLogo();
}

void Mere::Lock::LockScreen::lock()
{
    showFullScreen();
    setGeometry(m_screen->geometry());
    windowHandle()->setScreen(m_screen);
    setVisible(true);

    applyLockTheme();
}

void Mere::Lock::LockScreen::unlock()
{
    m_time->hide();
    m_text->hide();
}

void Mere::Lock::LockScreen::block()
{
    m_blocktime = QTime(0, m_config->blockTimeout());
    applyBlockTheme();

    m_time->show();
    m_text->show();
}

void Mere::Lock::LockScreen::unblock()
{
    m_blocktime = QTime(-1, -1);
    applyLockTheme();
}

void Mere::Lock::LockScreen::tick()
{
    m_elaspsetime = m_elaspsetime.addSecs(1);

    if (isBlocked())
    {
        m_blocktime = m_blocktime.addSecs(-1);
        m_time->setText(m_blocktime.toString("hh:mm:ss"));
    }
    else
    {
        m_time->setText(m_elaspsetime.toString("hh:mm:ss"));
    }
}

void Mere::Lock::LockScreen::restore()
{
    m_time->show();
    m_text->show();
}

bool Mere::Lock::LockScreen::isBlocked() const
{
    return m_blocktime.isValid();
}

void Mere::Lock::LockScreen::applyLockTheme()
{
    m_time->setText(m_elaspsetime.toString("hh:mm:ss"));
    setLockTimeStyle();
    setLockTimePosition();

    m_text->setText(tr("LockMessage"));
    setLockMessageStyle();
    setLockMessagePosition();
}

void Mere::Lock::LockScreen::applyBlockTheme()
{
    m_time->setText(m_blocktime.toString("hh:mm:ss"));
    setBlockTimeStyle();
    setBlockTimePosition();

    m_text->setText(tr("BlockMessage").arg(m_config->unlockAttempts()));
    setBlockMessageStyle();
    setBlockMessagePosition();
}

void Mere::Lock::LockScreen::setTime()
{
    m_time = new QLabel("00:00:00", this);
}

void Mere::Lock::LockScreen::setTimePosition()
{
    moveToCenter(m_time);

    QRect geometry = m_time->geometry();
    m_time->move(QPoint(geometry.x(), geometry.y() - geometry.height()/2));
}

void Mere::Lock::LockScreen::setTimeStyle(const QColor &color, const int size)
{
    setTextStyle(m_time, color, size);
}

void Mere::Lock::LockScreen::setLockTimeStyle()
{
    setTimeStyle(m_config->lockScreenTimeColor(), m_config->lockScreenTimeSize());
}

void Mere::Lock::LockScreen::setLockTimePosition()
{
    setTimePosition();
}

void Mere::Lock::LockScreen::setBlockTimeStyle()
{
    setTimeStyle(m_config->blockScreenTimeColor(), m_config->blockScreenTimeSize());
}

void Mere::Lock::LockScreen::setBlockTimePosition()
{
    setTimePosition();
}

void Mere::Lock::LockScreen::setMessage()
{
    m_text = new QLabel(this);
}

void Mere::Lock::LockScreen::setMessagePosition()
{
    moveToCenter(m_text);

    QRect geometry = m_text->geometry();
    m_text->move(QPoint(geometry.x(), geometry.y() + geometry.height()/2));
}

void Mere::Lock::LockScreen::setMessageStyle(const QColor &color, const int size)
{
    setTextStyle(m_text, color, size);
}

void Mere::Lock::LockScreen::setLockMessageStyle()
{
    setMessageStyle(m_config->lockScreenMessageColor(), m_config->lockScreenMessageSize());
}

void Mere::Lock::LockScreen::setLockMessagePosition()
{
    setMessagePosition();
}

void Mere::Lock::LockScreen::setBlockMessageStyle()
{
    setMessageStyle(m_config->blockScreenMessageColor(), m_config->blockScreenMessageSize());
}

void Mere::Lock::LockScreen::setBlockMessagePosition()
{
    moveToCenter(m_text);
    QRect geometry = m_text->geometry();
    m_text->move(QPoint(geometry.x(), geometry.y() + geometry.height()/2));
}

void Mere::Lock::LockScreen::setTextStyle(QLabel *label, const QColor &color, const int size)
{
    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, color);
    label->setPalette(palette);

    QFont font = label->font();
    font.setPointSize(size);
    label->setFont(font);

    label->adjustSize();
}

void Mere::Lock::LockScreen::moveToCenter(QLabel *label)
{
    QRect screenRect = m_screen->geometry();
    QRect screenGeometry(0, 0, screenRect.width(), screenRect.height());

    QRect labelRect = label->fontMetrics().boundingRect(label->text());
    QRect labelGeometry(0, 0, labelRect.width(), labelRect.height());

    label->move(screenGeometry.center() - labelGeometry.center());
}

void Mere::Lock::LockScreen::setBackground()
{
    QPalette pal = palette();
    QPixmap pixmap = m_config->lockScreenBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->lockScreenBackgroundColor();
        pal.setColor(QPalette::Window, color);
    }

    setPalette(pal);
}

void Mere::Lock::LockScreen::setScreenLogo()
{
    if(!m_config->lockScreenLogoShow()) return;

    QString logo(m_config->lockScreenLogo().c_str());
    if (logo.isEmpty()) return;

    QPixmap pixmap(logo);
    if (pixmap.isNull())
    {
        std::cout << "Unable to create image for screen logo; please check the image path." << logo.toStdString() << std::endl;
        return;
    }

    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setMaximumSize(QSize(128, 35));
    label->setPixmap(pixmap);

    label->move(25, m_screen->size().height() - label->height() - 25);
}
