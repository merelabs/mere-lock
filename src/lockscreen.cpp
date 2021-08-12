#include "lockscreen.h"
#include "lockprompt.h"
#include "locker.h"
#include "config.h"

#include <QDebug>
#include <QTimer>
#include <QScreen>
#include <QWindow>
#include <QVBoxLayout>
#include <QApplication>

LockScreen::~LockScreen()
{
    releaseMouse();
    releaseKeyboard();

    if(m_prompt)
    {
        delete m_prompt;
        m_prompt = nullptr;
    }
}

LockScreen::LockScreen(QScreen *screen, QWidget *parent)
    : QWidget(parent),
      m_screen(screen),
      m_prompt(nullptr)
{
    setObjectName("LockScreen");

    setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
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

void LockScreen::lock()
{
    showFullScreen();
    windowHandle()->setScreen(m_screen);
    setVisible(true);
}

void LockScreen::unlock()
{

}

void LockScreen::prompt()
{
    if (!m_prompt)
    {
        m_prompt = new LockPrompt(this);
        connect(m_prompt, &LockPrompt::keyboardReleased, [&](){
            grabKeyboard();
        });

        connect(m_prompt, &LockPrompt::verified, [&](){
            grabKeyboard();
            emit verified();
        });
    }

    if (!m_prompt->isHidden()) return;

    m_prompt->showNormal();
}

void LockScreen::setMessage()
{
    QLabel *label = new QLabel(tr("LockMessage"), this);
    label->move(m_screen->virtualGeometry().center() - label->fontMetrics().boundingRect(label->text()).center());
}

void LockScreen::setBackground()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    QString background(config->background().c_str());

    QPalette pal = palette();
    if (background.startsWith("#"))
    {
background:
        QColor color(background);
        if (!color.isValid())
            color.setNamedColor("#0B6623");

        pal.setColor(QPalette::Window, QColor(background));
    }
    else
    {
        QPixmap pixmap(background);
        if(pixmap.isNull())
        {
            background = "#0B6623";
            goto background;
        }

        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);

        pal.setBrush(QPalette::Window, pixmap);
    }
    setPalette(pal);
}

void LockScreen::setScreenLogo()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    if(!config->logoshow()) return;

    QString logo(config->logo().c_str());
    if (logo.isEmpty()) return;

    QPixmap pixmap(logo);

    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setMaximumSize(QSize(128, 35));
    label->setPixmap(pixmap);

    QSize size = m_screen->availableVirtualSize();

    label->move(25, size.height() - label->height() - 25);
}

bool LockScreen::eventFilter(QObject *obj, QEvent *event)
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
