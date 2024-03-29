#include "prompt.h"
#include "config.h"
#include "ticker.h"
#include "waitbar.h"
#include "secret.h"

#include "mere/utils/stringutils.h"

#include <iostream>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

Mere::Lock::Prompt::~Prompt()
{

}

Mere::Lock::Prompt::Prompt(QWidget *parent)
    : QWidget(parent),
      m_ticker(new Mere::Lock::Ticker(5, this)),
      m_config(Mere::Lock::Config::instance())
{
    setObjectName("Prompt");
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

    connect(m_ticker, &Mere::Lock::Ticker::tick, this, [&](){
        std::cout << "you can restart counting! :)" << std::endl;
        m_ticker->stop();
        m_timeout->start();
    });

    connect(m_timeout, &Mere::Lock::Waitbar::timeout, this, [&](){
        emit cancelled();
    });

    connect(m_secret, &Mere::Lock::Secret::changed, this, [&](){
        m_timeout->reset();
        m_ticker->start();
    });

    connect(m_secret, &Mere::Lock::Secret::entered, this, [&](){
        emit attempted();
    });

    connect(m_secret, &Mere::Lock::Secret::escaped, this, [&](){
        emit cancelled();
    });
}

void Mere::Lock::Prompt::initUI()
{
    QSpacerItem *topSpacer = new QSpacerItem(1, 120, QSizePolicy::Fixed, QSizePolicy::Minimum);
    this->layout()->addItem(topSpacer);

    initMessageUI();

    m_secret = new Mere::Lock::Secret(this);
    this->layout()->addWidget(m_secret);

    QSpacerItem *bottomSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->layout()->addItem(bottomSpacer);

    m_result = new QLabel(tr("UnlockAttempt"), this);
    m_result->setObjectName("UnlockAttempt");

    QSizePolicy sizePolicy = m_result->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    m_result->setSizePolicy(sizePolicy);

    this->layout()->addWidget(m_result);

    m_result->setVisible(false);
}

void Mere::Lock::Prompt::initMessageUI()
{
    QLabel *label = new QLabel(tr("UnlockPrompt"), this);
    label->setObjectName("UnlockPrompt");
    label->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(label);

    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText, m_config->unlockScreenPromptMessageColor());
    label->setPalette(palette);

    QFont font = label->font();
    font.setPointSize(m_config->unlockScreenPromptMessageSize());
    label->setFont(font);

    label->move(geometry().center() - label->fontMetrics().boundingRect(label->text()).center());
}

void Mere::Lock::Prompt::clear()
{
    m_secret->clear();

    m_result->setVisible(false);
}

void Mere::Lock::Prompt::setTimeout()
{
    m_timeout = new Mere::Lock::Waitbar(this);
}

void Mere::Lock::Prompt::setVisible(bool visible)
{
    if (visible)
    {
        clear();
        m_secret->setFocus();
        m_secret->grabKeyboard();

        m_ticker->start();
        m_timeout->stop();
    }
    else
    {
        m_secret->releaseKeyboard();

        m_ticker->stop();
        m_timeout->stop();
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
    QPalette pal = palette();
    QPixmap pixmap = m_config->unlockScreenPromptBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }
    else
    {
        QColor color = m_config->unlockScreenPromptBackgroundColor();
        pal.setColor(QPalette::Window, QColor(color));
    }

    setPalette(pal);
}

void Mere::Lock::Prompt::setPromptLogo()
{
    if(!m_config->unlockScreenPromptLogoShow()) return;

    std::string path = m_config->unlockScreenPromptLogo();
    if (Mere::Utils::StringUtils::isBlank(path)) return;

    QPixmap pixmap(QString::fromStdString(path));
    if (pixmap.isNull())
    {
        std::cout << "Unable to create image for prompt logo; please check the image path." << path << std::endl;
        return;
    }

    QSize size(geometry().width() - 50, 96);
    pixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *label = new QLabel(this);
    label->setMargin(0);
    label->setContentsMargins(0, 0, 0, 0);
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumHeight(96);
    label->setMaximumHeight(96);
    label->setPixmap(pixmap);

    label->move(this->width()/2 - label->width()/2, 30);
}

std::string Mere::Lock::Prompt::input() const
{
    return m_secret->secret();
}

