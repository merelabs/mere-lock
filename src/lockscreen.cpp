#include "lockscreen.h"
#include "lockprompt.h"
#include "locker.h"
#include "config.h"

#include <iostream>
#include <QTimer>
#include <QScreen>
#include <QWindow>
#include <QVBoxLayout>
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
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      m_screen(screen),
      m_prompt(nullptr)
{
    setObjectName("LockScreen");

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

    setMessage();
    setBackground();
    setScreenLogo();

    grabMouse();
    grabKeyboard();

    installEventFilter(this);
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

}

void Mere::Lock::LockScreen::prompt()
{
    if (!m_prompt)
    {
        m_prompt = new Mere::Lock::LockPrompt(m_screen, this);
        connect(m_prompt, &Mere::Lock::LockPrompt::keyboardReleased, [&](){
            grabKeyboard();
        });

        connect(m_prompt, &Mere::Lock::LockPrompt::verified, [&](){
            grabKeyboard();
            emit verified();
        });

        connect(m_prompt, &Mere::Lock::LockPrompt::closed, [&](){
            showMessage();
        });
    }

    if (!m_prompt->isHidden()) return;

    hideMessage();
    m_prompt->showNormal();
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

void Mere::Lock::LockScreen::hideMessage()
{
  QLabel *message = findChild<QLabel *>("LockMessage");
  message->hide();
}

void Mere::Lock::LockScreen::showMessage()
{
  QLabel *message = findChild<QLabel *>("LockMessage");
  message->show();
}

bool Mere::Lock::LockScreen::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::MouseMove)
    {

#ifdef QT_DEBUG
        // - test code
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            ::exit(0);
        // - end of test code
#endif
        prompt();

        return true;
    }

    return QObject::eventFilter(obj, event);
}
