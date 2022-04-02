#include "lockscreen.h"
#include "lockprompt.h"
#include "locker.h"
#include "config.h"

#include <iostream>
#include <QTimer>
#include <QScreen>
#include <QWindow>
#include <QApplication>

Mere::Lock::LockScreen::~LockScreen()
{
    releaseMouse();
    releaseKeyboard();

    if(m_prompt)
    {
        delete m_prompt;
        m_prompt = nullptr;
    }
}

Mere::Lock::LockScreen::LockScreen(QScreen *screen, QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint),
      m_screen(screen),
      m_prompt(nullptr)
{
    setObjectName("LockScreen-" + screen->name());

//    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

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
}

void Mere::Lock::LockScreen::unlock()
{
    setVisible(false);
}

void Mere::Lock::LockScreen::setMessage()
{
    QLabel *label = new QLabel(tr("LockMessage"), this);
    label->setObjectName("LockMessage");

    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, config->screenMessageColor());
    label->setPalette(palette);

    QFont font = label->font();
    font.setPointSize(config->screenMessageSize());
    label->setFont(font);

    QRect rect = m_screen->geometry();
    QRect geometry(0, 0, rect.width(), rect.height());
    label->move(geometry.center() - label->fontMetrics().boundingRect(label->text()).center());
}

void Mere::Lock::LockScreen::setBackground()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette pal = palette();
    QPixmap pixmap = config->screenBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = config->screenBackgroundColor();
        pal.setColor(QPalette::Window, color);
    }

    setPalette(pal);
}

void Mere::Lock::LockScreen::setScreenLogo()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    if(!config->logoshow()) return;

    QString logo(config->logo().c_str());
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
