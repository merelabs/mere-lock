#include "lockprompt.h"

#include "mere/auth/service.h"

#include <QScreen>
#include <QVBoxLayout>
#include <QApplication>
#include <QGraphicsDropShadowEffect>

LockPrompt::~LockPrompt()
{
    if (m_prompt)
    {
        delete m_prompt;
        m_prompt = nullptr;
    }

    if (m_password)
    {
        delete m_password;
        m_password = nullptr;
    }

    if (m_result)
    {
        delete m_result;
        m_result = nullptr;
    }
}

LockPrompt::LockPrompt(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("MereLockPrompt");

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);

    resize(500, 300);
    moveToCenterScreen();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(249, 249, 249, 255));
    setAutoFillBackground(true);
    setPalette(pal);

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setColor(Qt::lightGray);
    dropShadowEffect->setOffset(10);
    dropShadowEffect->setBlurRadius(20);
    setGraphicsEffect(dropShadowEffect);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(50, 15, 50, 15);
    layout->setSpacing(10);

    initUI();
}

void LockPrompt::initUI()
{
    QSpacerItem *topSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(topSpacer);

    m_prompt = new QLabel("Enter your password and press return.", this);
    m_prompt->setObjectName("MereLockPrompt");
    m_prompt->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(m_prompt);

    m_password = new QLineEdit(this);
    m_password->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(m_password);

    QSpacerItem *bottomSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(bottomSpacer);

    m_result = new QLabel("* invalid attepmt to unlock.", this);
    m_result->setObjectName("MereLockPromptResult");

    QSizePolicy sizePolicy = m_result->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_result->setSizePolicy(sizePolicy);

    this->layout()->addWidget(m_result);

    m_result->setVisible(false);
    connect(m_password, SIGNAL(returnPressed()), this, SLOT(verify()));
}

QString LockPrompt::password() const
{
    return m_password->text();
}

void LockPrompt::clear()
{
    m_password->clear();
}

void LockPrompt::setVisible(bool visible)
{
    if (visible)
    {
        m_password->grabKeyboard();
        emit keyboardGrabbed();
    }
    else
    {
        m_password->releaseKeyboard();
        emit keyboardReleased();
    }

    QWidget::setVisible(visible);
}

void LockPrompt::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Escape)
    {
        clear();
        setVisible(false);
    }

    if (keyEvent->key() == Qt::Key_Enter)
    {
        setVisible(false);
    }
}

void LockPrompt::verify()
{
    Mere::Auth::Service service;
    bool ok = service.verify(m_password->text().toStdString());
    if (!ok)
    {
        m_result->setVisible(true);
        return;
    }

    emit verified();
}

void LockPrompt::moveToCenterScreen()
{
    QRect rect = QApplication::primaryScreen()->geometry();
    QPoint center(rect.center() - this->rect().center());
    move(center);
}
