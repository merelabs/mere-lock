#include "lockprompt.h"
#include "config.h"

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
    setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);

    resize(500, 300);
    QScreen *screen = QApplication::primaryScreen();
    move(screen->virtualGeometry().center() - this->rect().center());

    setShadow();
    setBackground();
    setPromptLogo();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(50, 15, 50, 15);
    layout->setSpacing(10);

    initUI();
}

void LockPrompt::initUI()
{
    QSpacerItem *topSpacer = new QSpacerItem(1, 100, QSizePolicy::Fixed, QSizePolicy::Minimum);
    this->layout()->addItem(topSpacer);

    m_prompt = new QLabel("Enter your password and press return.", this);
    m_prompt->setObjectName("MereLockPrompt");
    m_prompt->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(m_prompt);

    m_password = new QLineEdit(this);
    m_password->setAlignment(Qt::AlignCenter);
    m_password->setEchoMode(QLineEdit::Password);
    this->layout()->addWidget(m_password);

    QSpacerItem *bottomSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(bottomSpacer);

    m_result = new QLabel("* sorry, incorrect attepmt to unlock screen.", this);
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
        clear();
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

void LockPrompt::setShadow()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    QString shadow(config->promptshadow().c_str());

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setColor(shadow);
    dropShadowEffect->setOffset(10);
    dropShadowEffect->setBlurRadius(20);
    setGraphicsEffect(dropShadowEffect);
}

void LockPrompt::setBackground()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    QString background(config->promptbackground().c_str());

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

void LockPrompt::setPromptLogo()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    if(!config->promptlogoshow()) return;

    QString logo(config->promptlogo().c_str());
    if (logo.isEmpty()) return;

    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setMinimumSize(QSize(48, 48));
    label->setPixmap(QPixmap(logo));
//    label->setStyleSheet("border: 1px solid black;");

    label->move(this->width()/2 - label->width()/2, 30);
}

void LockPrompt::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Enter)
        setVisible(false);
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
