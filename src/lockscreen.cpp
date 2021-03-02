#include "lockscreen.h"
#include "lockprompt.h"
#include "locker.h"
#include "config.h"

#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>

LockScreen::~LockScreen()
{
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

    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(config->background().c_str()));
    setAutoFillBackground(true);
    setPalette(pal);

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
    QTimer::singleShot(100, this, &QWidget::grabKeyboard);
}

void LockScreen::keyReleaseEvent(QKeyEvent *keyEvent)
{
    Q_UNUSED(keyEvent)

    m_prompt->showNormal();
}
