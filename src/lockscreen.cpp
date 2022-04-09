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
      m_prompt(nullptr),
      m_config(Mere::Lock::Config::instance())
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

    m_text->setText(tr("LockMessage"));
}

void Mere::Lock::LockScreen::unlock()
{
    setVisible(false);
}

void Mere::Lock::LockScreen::block()
{
    m_text->setText(tr("BlockMessage").arg(m_config->attempts()));
    m_text->show();
}

void Mere::Lock::LockScreen::setMessage()
{
    m_text = new QLabel(tr("LockMessage"), this);

    QPalette palette = m_text->palette();
    palette.setColor(QPalette::WindowText, m_config->screenMessageColor());
    m_text->setPalette(palette);

    QFont font = m_text->font();
    font.setPointSize(m_config->screenMessageSize());
    m_text->setFont(font);

    QRect rect = m_screen->geometry();
    QRect geometry(0, 0, rect.width(), rect.height());
    m_text->move(geometry.center() - m_text->fontMetrics().boundingRect(m_text->text()).center());
}

void Mere::Lock::LockScreen::setBackground()
{
    QPalette pal = palette();
    QPixmap pixmap = m_config->screenBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->screenBackgroundColor();
        pal.setColor(QPalette::Window, color);
    }

    setPalette(pal);
}

void Mere::Lock::LockScreen::setScreenLogo()
{
    if(!m_config->logoshow()) return;

    QString logo(m_config->logo().c_str());
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

void Mere::Lock::LockScreen::hideMessage()
{
  m_text->hide();
}

void Mere::Lock::LockScreen::showMessage()
{
  m_text->show();
}
