#include "lockprompt.h"
#include "config.h"

#include "mere/auth/service.h"

#include <iostream>
#include <QDateTime>
#include <QScreen>
#include <QKeyEvent>
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

LockPrompt::LockPrompt(QScreen *screen, QWidget *parent)
    : QWidget(parent),
      m_screen(screen)
{
    setObjectName("LockPrompt");
    setWindowFlags (Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::WindowModal);

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

    resize(500, 300);
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

    initMessageUI();

    m_password = new QLineEdit(this);
    m_password->setAlignment(Qt::AlignCenter);
    m_password->setEchoMode(QLineEdit::Password);
    this->layout()->addWidget(m_password);

    QSpacerItem *bottomSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(bottomSpacer);

    m_result = new QLabel(tr("LockAttempt"), this);
    m_result->setObjectName("LockAttempt");

    QSizePolicy sizePolicy = m_result->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_result->setSizePolicy(sizePolicy);

    this->layout()->addWidget(m_result);

    m_result->setVisible(false);
    connect(m_password, SIGNAL(returnPressed()), this, SLOT(verify()));
}

void LockPrompt::initMessageUI()
{
    QLabel *label = new QLabel(tr("LockPrompt"), this);
    label->setObjectName("LockPrompt");
    label->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(label);

    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, config->promptMessageColor());
    label->setPalette(palette);

    QFont font = label->font();
    font.setPointSize(config->promptMessageSize());
    label->setFont(font);

    label->move(m_screen->virtualGeometry().center() - label->fontMetrics().boundingRect(label->text()).center());
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

        emit closed();
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

    QPalette pal = palette();
    QPixmap pixmap = config->promptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = config->promptBackgroundColor();
        pal.setColor(QPalette::Window, QColor(color));
    }

    setPalette(pal);
}

void LockPrompt::setPromptLogo()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    if(!config->promptlogoshow()) return;

    QString logo(config->promptlogo().c_str());
    if (logo.isEmpty()) return;

    QPixmap pixmap(logo);
    if (pixmap.isNull())
    {
        std::cout << "Unable to create image for prompt logo; please check the image path." << logo.toStdString() << std::endl;
        return;
    }

    QSize size(64, 64);
    pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *label = new QLabel(this);
    label->setMargin(0);
    label->setContentsMargins(0, 0, 0, 0);
    label->setAlignment(Qt::AlignCenter);
    label->setScaledContents(true);
    label->setMinimumSize(size);
    label->setPixmap(pixmap);
    //label->setStyleSheet("border: 1px solid black;");

    label->move(this->width()/2 - label->width()/2, 30);
}

void LockPrompt::verify()
{
    bool ok = false;

    Mere::Lock::Config *config = Mere::Lock::Config::instance();
    std::string password = config->password();
    if (!password.empty())
    {
        ok = (password.compare(m_password->text().toStdString()) == 0);
    }
    else
    {
        Mere::Auth::Service service;
        ok = service.verify(m_password->text().toStdString());
    }

    if (!ok)
    {
        m_result->setVisible(true);
        return;
    }

    emit verified();
}

bool LockPrompt::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress  /*|| event->type() == QEvent::KeyRelease*/ ||
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
