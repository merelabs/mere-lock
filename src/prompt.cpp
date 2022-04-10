#include "prompt.h"
#include "config.h"

#include <iostream>
#include <QDateTime>
#include <QScreen>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QtMath>

//static
const int Mere::Lock::Prompt::timeoutCheckInterval = 500;
const int Mere::Lock::Prompt::timeoutStartOffset = 5000;

Mere::Lock::Prompt::~Prompt()
{

}

Mere::Lock::Prompt::Prompt(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("UnlockPrompt");
    setWindowFlags (Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::WindowModal);

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

    resize(500, 300);

    QRect rect = parent->geometry();
    QRect geometry(0, 0, rect.width(), rect.height());
    move(geometry.center() - this->rect().center());

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

void Mere::Lock::Prompt::initUI()
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

    m_result = new QLabel(tr("UnlockAttempt"), this);
    m_result->setObjectName("UnlockAttempt");

    QSizePolicy sizePolicy = m_result->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_result->setSizePolicy(sizePolicy);

    this->layout()->addWidget(m_result);

    m_result->setVisible(false);

    connect(m_password, &QLineEdit::returnPressed, this, [&](){
        emit attempted();
    });
}

void Mere::Lock::Prompt::initMessageUI()
{
    QLabel *label = new QLabel(tr("UnlockPrompt"), this);
    label->setObjectName("UnlockPrompt");
    label->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(label);

    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, config->promptMessageColor());
    label->setPalette(palette);

    QFont font = label->font();
    font.setPointSize(config->promptMessageSize());
    label->setFont(font);

    label->move(geometry().center() - label->fontMetrics().boundingRect(label->text()).center());
}

void Mere::Lock::Prompt::clear()
{
    m_password->clear();
    m_result->setVisible(false);
    m_timeoutPanel->setGeometry(0, 0, 0, 2);
}

void Mere::Lock::Prompt::setTimeout()
{
    if (m_timeoutTimer) return;

    m_timeoutTimer = new QTimer(this);
    m_timeoutTimer->setInterval(timeoutCheckInterval);

    connect(m_timeoutTimer, &QTimer::timeout, this, [&]{
        Mere::Lock::Config *config = Mere::Lock::Config::instance();
        qint64 lapse = QDateTime::currentMSecsSinceEpoch() - m_timeoutStart;
        if ( lapse > (config->promptTimeout() * 1000 + timeoutStartOffset + timeoutCheckInterval))
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
            animation->setEndValue(QRect(0, 0, this->width()/(config->promptTimeout() * 2) * qFloor((lapse - timeoutStartOffset) / timeoutCheckInterval), 2));
            animation->start();
        }
    });

    m_timeoutPanel = new QWidget(this);
    m_timeoutPanel->setGeometry(0, 0, 0, 2);
}

void Mere::Lock::Prompt::setVisible(bool visible)
{
    if (visible)
    {
        clear();
        m_timeoutStart = QDateTime::currentMSecsSinceEpoch();
        m_timeoutTimer->start();

        m_password->setFocus();
        m_password->grabKeyboard();
    }
    else
    {
        m_timeoutStart = 0;
        m_timeoutTimer->stop();
        m_timeoutPanel->setGeometry(0, 0, 0, 2);

        m_password->releaseKeyboard();
    }

    QWidget::setVisible(visible);
}

void Mere::Lock::Prompt::setShadow()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(10);
    shadowEffect->setBlurRadius(25);
    setGraphicsEffect(shadowEffect);
}

void Mere::Lock::Prompt::setBackground()
{
    Mere::Lock::Config *config = Mere::Lock::Config::instance();

    QPalette pal = palette();
    QPixmap pixmap = config->promptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = config->promptBackgroundColor();
        pal.setColor(QPalette::Window, QColor(color));
    }

    setPalette(pal);
}

void Mere::Lock::Prompt::setPromptLogo()
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

    QSize size(96, 94);
    pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *label = new QLabel(this);
    label->setMargin(0);
    label->setContentsMargins(0, 0, 0, 0);
    label->setAlignment(Qt::AlignCenter);
    label->setScaledContents(true);
    label->setMinimumSize(size);
    label->setPixmap(pixmap);

    label->move(this->width()/2 - label->width()/2, 30);
}

std::string Mere::Lock::Prompt::input() const
{
    return m_password->text().toStdString();
}

bool Mere::Lock::Prompt::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress )
    {
        m_timeoutStart = QDateTime::currentMSecsSinceEpoch();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Escape)
            emit cancelled();

        return true;
    }

    return false;
}