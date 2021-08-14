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
        m_prompt = new LockPrompt(m_screen, this);
        connect(m_prompt, &LockPrompt::keyboardReleased, [&](){
            grabKeyboard();
        });

        connect(m_prompt, &LockPrompt::verified, [&](){
            grabKeyboard();
            emit verified();
        });

        connect(m_prompt, &LockPrompt::closed, [&](){
            showMessage();
        });
    }

    if (!m_prompt->isHidden()) return;

    hideMessage();
    m_prompt->showNormal();
}

void LockScreen::setMessage()
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

    label->move(m_screen->virtualGeometry().center() - label->fontMetrics().boundingRect(label->text()).center());
}

void LockScreen::setBackground()
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
        pal.setColor(QPalette::Window, QColor(color));
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
    if (pixmap.isNull())
    {
        std::cout << "Unable to create image for screen logo; please check the image path." << logo.toStdString() << std::endl;
        return;
    }

    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setMaximumSize(QSize(128, 35));
    label->setPixmap(pixmap);

    QSize size = m_screen->availableVirtualSize();

    label->move(25, size.height() - label->height() - 25);
}

void LockScreen::hideMessage()
{
  QLabel *message = findChild<QLabel *>("LockMessage");
  message->hide();
}

void LockScreen::showMessage()
{
  QLabel *message = findChild<QLabel *>("LockMessage");
  message->show();
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
