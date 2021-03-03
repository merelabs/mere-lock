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

    if (m_label)
    {
        delete m_label;
        m_label = nullptr;
    }

    if (m_prompt)
    {
        delete m_prompt;
        m_prompt = nullptr;
    }
}

LockScreen::LockScreen(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setCursor(Qt::BlankCursor);
    setMouseTracking(true);

    setBackground();
    setScreenLogo();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    m_label = new QLabel("Press any key to get the password prompt.");
    layout->addWidget(m_label);

    m_prompt = new LockPrompt(this);
    connect(m_prompt, &LockPrompt::keyboardReleased, [&](){
        grabKeyboard();
    });

    connect(m_prompt, &LockPrompt::verified, [&](){
        grabKeyboard();
        emit verified();
    });

    m_prompt->hide();

    grabMouse();
    grabKeyboard();

    installEventFilter(this);
}

void LockScreen::prompt()
{
    if (m_prompt->isHidden())
        m_prompt->showNormal();
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
        QPixmap pixmap(background);
        QScreen *primaryScreen = QApplication::primaryScreen();
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
        // - test code
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            ::exit(1);
        // - end of test code

        prompt();

        return true;
    }

    return QObject::eventFilter(obj, event);
}
