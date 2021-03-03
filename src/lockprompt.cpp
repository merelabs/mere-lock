#include "lockprompt.h"
#include "config.h"

#include "mere/auth/service.h"

#include <QDateTime>
#include <QScreen>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

//static
const int LockPrompt::timeoutCheckInterval = 500;
const int LockPrompt::timeoutStartOffset = 5000;

LockPrompt::~LockPrompt()
{

}

LockPrompt::LockPrompt(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("MereLockPrompt");
    setWindowFlags (Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::WindowModal);

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);

    resize(500, 300);
    QScreen *screen = QApplication::primaryScreen();
    move(screen->virtualGeometry().center() - this->rect().center());

    setShadow();
    setBackground();
    setPromptLogo();
    setTimeout();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(50, 15, 50, 15);
    layout->setSpacing(0);

    initUI();

    installEventFilter(this);
}

void LockPrompt::initUI()
{
    QSpacerItem *topSpacer = new QSpacerItem(1, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);
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

void LockPrompt::clear()
{
    m_password->clear();
}

void LockPrompt::setTimeout()
{
    if (m_timeoutTimer) return;

    m_timeoutTimer = new QTimer(this);
    m_timeoutTimer->setInterval(timeoutCheckInterval);

    connect(m_timeoutTimer, &QTimer::timeout, this, [&]{
        Mere::Lock::Config *config = Mere::Lock::Config::instance();
        qint64 lapse = QDateTime::currentMSecsSinceEpoch() - m_timeoutStart;
        if ( lapse > (config->timeout() * 1000 + timeoutStartOffset + timeoutCheckInterval))
        {
            setVisible(false);
        }
        else if (lapse < timeoutStartOffset + timeoutCheckInterval )
        {
            m_timeoutPanel->setGeometry(0, 0, 0, 2);
        }
        else
        {
            m_timeoutPanel->setStyleSheet("background: red;");
            QPropertyAnimation *animation = new QPropertyAnimation(m_timeoutPanel, "geometry", this);
            animation->setDuration(timeoutCheckInterval);
            animation->setEndValue(QRect(0, 0, this->width()/(config->timeout() * 2) * floor((lapse - timeoutStartOffset) / timeoutCheckInterval), 2));
            animation->start();
        }
    });

    m_timeoutPanel = new QWidget(this);
    m_timeoutPanel->setGeometry(0, 0, 0, 2);
}

void LockPrompt::setVisible(bool visible)
{
    if (visible)
    {
        clear();
        m_timeoutStart = QDateTime::currentMSecsSinceEpoch();
        m_timeoutTimer->start();

        grabMouse();
        m_password->setFocus();
        m_password->grabKeyboard();
        emit keyboardGrabbed();
    }
    else
    {
        m_timeoutStart = 0;
        m_timeoutTimer->stop();
        m_timeoutPanel->setGeometry(0, 0, 0, 2);

        releaseMouse();
        m_password->releaseKeyboard();
        emit keyboardReleased();

    }

    QWidget::setVisible(visible);
}

void LockPrompt::setShadow()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(10);
    shadowEffect->setBlurRadius(25);
    setGraphicsEffect(shadowEffect);
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

    QSize size(64, 64);
    QPixmap pixmap(logo);
    pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QLabel *label = new QLabel(this);
    label->setMargin(0);
    label->setContentsMargins(0, 0, 0, 0);
    label->setScaledContents(true);
    label->setMinimumSize(size);
    label->setPixmap(pixmap);
    //label->setStyleSheet("border: 1px solid black;");

    label->move(this->width()/2 - label->width()/2, 30);
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

bool LockPrompt::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress  || event->type() == QEvent::KeyRelease ||
        event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease || event->type() == QEvent::MouseMove)
    {
        m_timeoutStart = QDateTime::currentMSecsSinceEpoch();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Enter)
            setVisible(false);

        return true;
    }

    return QObject::eventFilter(obj, event);
}
