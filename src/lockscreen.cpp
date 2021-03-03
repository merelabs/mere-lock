#include "lockscreen.h"
#include "lockprompt.h"
#include "locker.h"
#include "config.h"

#include <QDebug>
#include <QTimer>
#include <QScreen>
#include <QVBoxLayout>
#include <QApplication>

LockScreen::~LockScreen()
{
    releaseMouse();
    releaseKeyboard();
}

LockScreen::LockScreen(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setCursor(Qt::BlankCursor);
    setMouseTracking(true);

    setMessage();
    setBackground();
    setScreenLogo();

    grabMouse();
    grabKeyboard();

    installEventFilter(this);
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
    QScreen *screen = QApplication::primaryScreen();

    QLabel *label = new QLabel("press any key or move mouse a bit", this);
    label->move(screen->virtualGeometry().center() - label->fontMetrics().boundingRect(label->text()).center());
}

void LockScreen::setBackground()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    QString background(config->background().c_str());

    QPalette pal = palette();
    if (background.startsWith("#"))
    {
        pal.setColor(QPalette::Window, QColor(background));
        setAutoFillBackground(true);
    }
    else
    {
        QScreen *primaryScreen = QApplication::primaryScreen();

        QPixmap pixmap(background);
        pixmap = pixmap.scaled(primaryScreen->availableVirtualSize(), Qt::IgnoreAspectRatio);

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

    QScreen *screen = QApplication::primaryScreen();
    QSize size = screen->availableVirtualSize();

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
            ::exit(1);
        // - end of test code
#endif
        prompt();

        return true;
    }

    return QObject::eventFilter(obj, event);
}
