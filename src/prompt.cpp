#include "prompt.h"
#include "config.h"
#include "ticker.h"
#include "timebar.h"
#include "secret.h"

#include "mere/utils/stringutils.h"

#include <iostream>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

Mere::Lock::Prompt::~Prompt()
{
    if (m_ticker)
    {
        m_ticker->stop();
        m_ticker->disconnect();
        delete m_ticker;
        m_ticker = nullptr;
    }

    if (m_secret)
    {
        m_secret->disconnect();
    }

    setGraphicsEffect(nullptr);
}

Mere::Lock::Prompt::Prompt(QWidget *parent)
    : QWidget(parent),
      m_ticker(new Mere::Lock::Ticker(5, this)),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("Prompt");
    setWindowFlags (Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::WindowModal);

//    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setAutoFillBackground(true);

    resize(500, 300);

    QRect rect = parent->geometry();
    QRect geometry(0, 0, rect.width(), rect.height());
    move(geometry.center() - this->rect().center());

    setTimeout();

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(10);
    shadowEffect->setBlurRadius(25);
    setGraphicsEffect(shadowEffect);

    initUI();

    grabMouse();
    grabKeyboard();
}

void Mere::Lock::Prompt::initUI()
{
    setBackground();
    setPromptLogo();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(50, 15, 50, 15);
    layout->setSpacing(0);

    QSpacerItem *topSpacer = new QSpacerItem(1, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);
    this->layout()->addItem(topSpacer);

    initMessageUI();

    m_secret = new Mere::Lock::Secret(this);
    this->layout()->addWidget(m_secret);

    QSpacerItem *bottomSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(bottomSpacer);

    m_message = new QLabel(tr("Attempt"), this);
    m_message->setObjectName("AttemptMessage");

    QSizePolicy sizePolicy = m_message->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_message->setSizePolicy(sizePolicy);

    this->layout()->addWidget(m_message);

    m_message->setVisible(false);

    connect(m_ticker, &Mere::Lock::Ticker::tick, this, [&](){
        m_ticker->stop();
        m_timebar->start();
    });

    connect(m_timebar, &Mere::Lock::Timebar::timeout, this, [&](){
        emit escaped();
    });

    connect(m_secret, &Mere::Lock::Secret::changed, this, [&](){
        m_ticker->start();
        m_timebar->reset();
    });

    connect(m_secret, &Mere::Lock::Secret::escaped, this, &Mere::Lock::Prompt::escaped);
//    connect(m_secret, &Mere::Lock::Secret::entered, [&](){
//        m_secret->setDisabled(true);
//    });
    connect(m_secret, &Mere::Lock::Secret::entered, this, &Mere::Lock::Prompt::entered);
}

void Mere::Lock::Prompt::initMessageUI()
{
    m_prompt = new QLabel(tr("Prompt"), this);
    m_prompt->setObjectName("Prompt");
    m_prompt->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(m_prompt);

    QPalette palette = m_prompt->palette();
    palette.setColor(QPalette::WindowText, m_config->promptMessageColor());
    m_prompt->setPalette(palette);

    QFont font = m_prompt->font();
    font.setPointSize(m_config->promptMessageSize());
    m_prompt->setFont(font);

    m_prompt->move(geometry().center() - m_prompt->fontMetrics().boundingRect(m_prompt->text()).center());
}

void Mere::Lock::Prompt::clear()
{
    m_secret->clear();

    m_message->setVisible(false);
}

void Mere::Lock::Prompt::setTimeout()
{
    m_timebar = new Mere::Lock::Timebar(this);
}

void Mere::Lock::Prompt::setVisible(bool visible)
{
    if (visible)
    {
        clear();
        m_secret->setFocus();
        m_secret->grabKeyboard();

        m_ticker->start();
        m_timebar->stop();
    }
    else
    {
        m_secret->releaseKeyboard();

        m_ticker->stop();
        m_timebar->stop();
    }

    QWidget::setVisible(visible);
}

void Mere::Lock::Prompt::setBackground()
{
    QPalette pal = palette();
    QPixmap pixmap = m_config->promptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->promptBackgroundColor();
        if (color.isValid())
        {
            pal.setColor(QPalette::Window, QColor(color));
        }
    }

    setPalette(pal);
}

void Mere::Lock::Prompt::setPromptLogo()
{
    m_logo = new QLabel(this);
    m_logo->setMargin(0);
    m_logo->setContentsMargins(0, 0, 0, 0);
    m_logo->setAlignment(Qt::AlignCenter);
    m_logo->setMinimumHeight(96);
    m_logo->setMaximumHeight(96);

    m_logo->move(this->width()/2 - m_logo->width()/2, 30);

    if(!m_config->promptLogoShow()) return;
    setLogo(m_config->promptLogo());
}

void Mere::Lock::Prompt::setLogo(QPixmap pixmap)
{
    if (pixmap.isNull()) return;

    QSize size(geometry().width() - 50, 96);
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_logo->setPixmap(pixmap);
}

std::string Mere::Lock::Prompt::input() const
{
    return m_secret->secret();
}

void Mere::Lock::Prompt::prompt(const std::string &prompt)
{
    m_prompt->setText(QString::fromStdString(prompt));
}

void Mere::Lock::Prompt::message(const std::string &message)
{
    m_message->setText(QString::fromStdString(message));
    if(m_message->isHidden()) m_message->show();
}

void Mere::Lock::Prompt::prompt()
{
    showNormal();
}
