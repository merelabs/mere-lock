#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <QApplication>
#include <iostream>

//
// Lock Screen
//
static const std::string KEY_LOCK_SCREEN_BACKGROUND       = "mere.lock.screen.background";

static const std::string KEY_LOCK_SCREEN_STOPWATCH_FONT   = "mere.lock.screen.stopwatch.font";
static const std::string KEY_LOCK_SCREEN_STOPWATCH_COLOR  = "mere.lock.screen.stopwatch.color";

static const std::string KEY_LOCK_SCREEN_MESSAGE_COLOR    = "mere.lock.screen.message.font.color";
static const std::string KEY_LOCK_SCREEN_MESSAGE_FONT     = "mere.lock.screen.message.font.size";

//
// Block Screen
//
static const std::string KEY_BLOCK_SCREEN_BACKGROUND      = "mere.lock.block.screen.background";

static const std::string KEY_BLOCK_SCREEN_STOPWATCH_FONT  = "mere.lock.block.screen.stopwatch.font.size";
static const std::string KEY_BLOCK_SCREEN_STOPWATCH_COLOR = "mere.lock.block.screen.stopwatch.font.color";

static const std::string KEY_BLOCK_SCREEN_MESSAGE_FONT    = "mere.lock.block.screen.message.font.size";
static const std::string KEY_BLOCK_SCREEN_MESSAGE_COLOR   = "mere.lock.block.screen.message.font.color";

static const std::string KEY_LOCK_BLOCK_TIMEOUT           = "mere.lock.block.timeout";
static const std::string VAL_LOCK_BLOCK_TIMEOUT           = "1";

//
// Unlock Prompt
//
static const std::string KEY_UNLOCK_PROMPT_BACKGROUND     = "mere.lock.unlock.prompt.background";

static const std::string KEY_UNLOCK_PROMPT_MESSAGE_FONT   = "mere.lock.unlock.prompt.message.font.size";
static const std::string KEY_UNLOCK_PROMPT_MESSAGE_COLOR  = "mere.lock.unlock.prompt.message.font.color";

static const std::string KEY_UNLOCK_PROMPT_LOGO           = "mere.lock.unlock.prompt.logo";
static const std::string VAL_UNLOCK_PROMPT_LOGO           = "/usr/local/share/mere/lock/freebsd-logo.png";

static const std::string KEY_UNLOCK_PROMPT_LOGO_SHOW      = "mere.lock.unlock.prompt.logo.show";
static const std::string VAL_UNLOCK_PROMPT_LOGO_SHOW      = "true";

static const std::string KEY_UNLOCK_PROMPT_TIMEOUT        = "mere.lock.unlock.prompt.timeout";
static const std::string VAL_UNLOCK_PROMPT_TIMEOUT        = "15";

//
// Generic
//
static const std::string KEY_UNLOCK_ATTEMPTS              = "mere.lock.unlock.attempts";
static const std::string VAL_UNLOCK_ATTEMPTS              = "3";

static const std::string KEY_LOCK_LOGO                    = "mere.lock.logo";
static const std::string VAL_LOCK_LOGO                    = "/usr/local/share/mere/lock/mere-logo.png";

static const std::string KEY_LOCK_LOGO_SHOW               = "mere.lock.logo.show";
static const std::string VAL_LOCK_LOGO_SHOW               = "true";

Mere::Lock::Config::Config() :
    Mere::Lock::Config::Config("mere/lock.conf", Mere::Config::Spec::Strict::Soft)
{
}

Mere::Lock::Config::Config(const std::string &path, const Mere::Config::Spec::Strict &strict) :
    Mere::Config::KVConfig(path, strict)
{
}

int Mere::Lock::Config::validate() const
{
    std::cout << qApp->translate("LockConfig", "LockConfigValueCheck").toStdString() << std::endl;

    int err = 0;

//    err = checkLockScreenBackground()     ? err : 1;
//    err = checkLockScreenStopwatchFont()  ? err : 1;
//    err = checkLockScreenStopwatchColor() ? err : 1;
//    err = checkLockScreenMessageFont()    ? err : 1;
//    err = checkLockScreenMessageColor()   ? err : 1;
//    err = checkLockScreenLogo()           ? err : 1;
//    err = checkLockScreenLogoShow()       ? err : 1;

//    err = checkBlockScreenBackground()    ? err : 1;
//    err = checkBlockScreenStopwatchFont() ? err : 1;
//    err = checkBlockScreenStopwatchColor()? err : 1;
//    err = checkBlockScreenMessageFont()   ? err : 1;
//    err = checkBlockScreenMessageColor()  ? err : 1;
//    err = checkBlockTimeout()             ? err : 1;

//    err = checkUnlockPromptBackground()   ? err : 1;
//    err = checkUnlockPromptLogo()         ? err : 1;
//    err = checkUnlockPromptLogoShow()     ? err : 1;
//    err = checkUnlockPromptMessageColor() ? err : 1;
//    err = checkUnlockPromptMessageFont()  ? err : 1;

//    err = checkUnlockPromptTimeout()      ? err : 1;
//    err = checkUnlockAttempts()           ? err : 1;


    if(err)
        std::cout << qApp->translate("LockConfig", "LockConfigValueCheckFailed").toStdString() << std::endl;

    return err;
}

std::string Mere::Lock::Config::password() const
{
    return this->get("mere.lock.password");
}

void Mere::Lock::Config::password(const std::string &password)
{
    this->set("mere.lock.password", password.c_str());
}

unsigned int Mere::Lock::Config::timeout() const
{
    std::string value = this->get("mere.lock.timeout");
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return 0;

    return Mere::Utils::StringUtils::toInt(value);
}

void Mere::Lock::Config::timeout(unsigned int timeout)
{
    this->set("mere.lock.timeout", std::to_string(timeout));
}

QVariant Mere::Lock::Config::lockScreenBackground() const
{
    return background(KEY_LOCK_SCREEN_BACKGROUND, QColor("#0B6623"));
}

bool Mere::Lock::Config::checkLockScreenBackground() const
{
    return checkBackground(KEY_LOCK_SCREEN_BACKGROUND);
}

QFont Mere::Lock::Config::lockScreenStopwatchFont() const
{
    return this->font(KEY_LOCK_SCREEN_STOPWATCH_FONT, QFont("Ubuntu", 92));
}

bool Mere::Lock::Config::checkLockScreenStopwatchFont() const
{
    return checkFont(KEY_LOCK_SCREEN_STOPWATCH_FONT);
}

QColor Mere::Lock::Config::lockScreenStopwatchColor() const
{
    return this->color(KEY_LOCK_SCREEN_STOPWATCH_COLOR, QColor("#0B6623"));
}

bool Mere::Lock::Config::checkLockScreenStopwatchColor() const
{
    return checkColor(KEY_LOCK_SCREEN_STOPWATCH_COLOR);
}

QColor Mere::Lock::Config::lockScreenMessageColor() const
{
    return this->color(KEY_LOCK_SCREEN_MESSAGE_COLOR, QColor("#000"));
}

bool Mere::Lock::Config::checkLockScreenMessageColor() const
{
    return checkColor(KEY_LOCK_SCREEN_MESSAGE_COLOR);
}

QFont Mere::Lock::Config::lockScreenMessageFont() const
{
    return this->font(KEY_LOCK_SCREEN_MESSAGE_FONT, QFont("Ubuntu", 10));
}

bool Mere::Lock::Config::checkLockScreenMessageFont() const
{
    return checkFont(KEY_LOCK_SCREEN_MESSAGE_FONT);
}

QVariant Mere::Lock::Config::blockScreenBackground() const
{
    return background(KEY_BLOCK_SCREEN_BACKGROUND, QColor("#FF0000"));
}

bool Mere::Lock::Config::checkBlockScreenBackground() const
{
    return checkBackground(KEY_BLOCK_SCREEN_BACKGROUND);
}

QColor Mere::Lock::Config::blockScreenStopwatchColor() const
{
    return this->color(KEY_BLOCK_SCREEN_STOPWATCH_COLOR, QColor("#D6ED17"));
}

bool Mere::Lock::Config::checkBlockScreenStopwatchColor() const
{
    return checkColor(KEY_BLOCK_SCREEN_STOPWATCH_COLOR);
}

QFont Mere::Lock::Config::blockScreenStopwatchFont() const
{
    return this->font(KEY_BLOCK_SCREEN_STOPWATCH_FONT, QFont("Ubuntu", 92));
}

bool Mere::Lock::Config::checkBlockScreenStopwatchFont() const
{
    return checkFont(KEY_BLOCK_SCREEN_STOPWATCH_FONT);
}

QColor Mere::Lock::Config::blockScreenMessageColor() const
{
    return this->color(KEY_BLOCK_SCREEN_MESSAGE_COLOR, QColor("#000"));
}

bool Mere::Lock::Config::checkBlockScreenMessageColor() const
{
    return checkColor(KEY_BLOCK_SCREEN_MESSAGE_COLOR);
}

QFont Mere::Lock::Config::blockScreenMessageFont() const
{
    return this->font(KEY_BLOCK_SCREEN_MESSAGE_FONT, QFont("Ubuntu", 10));
}

bool Mere::Lock::Config::checkBlockScreenMessageFont() const
{
    return checkInt(KEY_BLOCK_SCREEN_MESSAGE_FONT);
}

unsigned int Mere::Lock::Config::blockTimeout() const
{
    std::string value = this->get(KEY_LOCK_BLOCK_TIMEOUT);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_BLOCK_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkBlockTimeout() const
{
    return checkInt(KEY_LOCK_BLOCK_TIMEOUT);
}

QVariant Mere::Lock::Config::unlockPromptBackground() const
{
    return background(KEY_UNLOCK_PROMPT_BACKGROUND, QColor("#FFF"));
}

bool Mere::Lock::Config::checkUnlockPromptBackground() const
{
    return checkBackground(KEY_UNLOCK_PROMPT_BACKGROUND);
}

std::string Mere::Lock::Config::unlockPromptLogo() const
{
    return value(KEY_UNLOCK_PROMPT_LOGO, VAL_UNLOCK_PROMPT_LOGO);
}

bool Mere::Lock::Config::checkUnlockPromptLogo() const
{
    return checkLogo(KEY_UNLOCK_PROMPT_LOGO);
}

bool Mere::Lock::Config::unlockPromptLogoShow() const
{
    std::string value = this->get(KEY_UNLOCK_PROMPT_LOGO_SHOW);
    if (value.empty()) return true;

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkUnlockPromptLogoShow() const
{
    return checkBool(KEY_UNLOCK_PROMPT_LOGO_SHOW);
}

QColor Mere::Lock::Config::unlockPromptMessageColor() const
{
    return this->color(KEY_UNLOCK_PROMPT_MESSAGE_COLOR, QColor("#000"));
}

bool Mere::Lock::Config::checkUnlockPromptMessageColor() const
{
    return checkColor(KEY_UNLOCK_PROMPT_MESSAGE_COLOR);
}

QFont Mere::Lock::Config::unlockPromptMessageFont() const
{
    return this->font(KEY_UNLOCK_PROMPT_MESSAGE_FONT, QFont("Ubuntu", 10));
}

bool Mere::Lock::Config::checkUnlockPromptMessageFont() const
{
    return checkInt(KEY_UNLOCK_PROMPT_MESSAGE_FONT);
}

unsigned int Mere::Lock::Config::unlockPromptTimeout() const
{
    std::string value = this->get(KEY_UNLOCK_PROMPT_TIMEOUT);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_UNLOCK_PROMPT_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockPromptTimeout() const
{
    return checkInt(KEY_UNLOCK_PROMPT_TIMEOUT);
}

unsigned int Mere::Lock::Config::unlockAttempts() const
{
    std::string value = this->get(KEY_UNLOCK_ATTEMPTS);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_UNLOCK_ATTEMPTS);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockAttempts() const
{
    return checkInt(KEY_UNLOCK_ATTEMPTS);
}

std::string Mere::Lock::Config::lockScreenLogo() const
{
    return value(KEY_LOCK_LOGO, VAL_LOCK_LOGO);
}

bool Mere::Lock::Config::checkLockScreenLogo() const
{
    return checkLogo(KEY_LOCK_LOGO);
}

bool Mere::Lock::Config::lockScreenLogoShow() const
{
    std::string value = this->get(KEY_LOCK_LOGO_SHOW);
    if (value.empty()) return true;

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkLockScreenLogoShow() const
{
    return checkBool(KEY_LOCK_LOGO_SHOW);
}

bool Mere::Lock::Config::checkBackground(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    if(value.at(0) == '#')
        return checkColor(key, value);
    else if(value.at(0) == '/')
        return checkImage(key, value);

    std::cout << qApp->translate("LockConfig", "LockConfigValueInvalid").arg(key.c_str()).arg(value.c_str()).toStdString() << std::endl;

    return false;
}

bool Mere::Lock::Config::checkColor(const std::string &key, const std::string &color) const
{
    QColor c(QString::fromStdString(color));
    if (!c.isValid())
    {
        std::cout << qApp->translate("LockConfig", "LockConfigValueInvalidColor").arg(key.c_str()).arg(color.c_str()).toStdString() << std::endl;

        return false;
    }

    return true;
}

bool Mere::Lock::Config::checkLogo(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    return checkImage(key, value);
}

bool Mere::Lock::Config::checkImage(const std::string &key, const std::string &path) const
{
    if(Mere::Utils::FileUtils::isNotExist(path))
    {
        std::cout << qApp->translate("LockConfig", "LockConfigValueInvalidFile").arg(key.c_str()).arg(path.c_str()).toStdString() << std::endl;

        return false;
    }

    QPixmap pixmap(QString::fromStdString(path));
    if(pixmap.isNull())
    {
        std::cout << qApp->translate("LockConfig", "LockConfigValueInvalidImage").arg(key.c_str()).arg(path.c_str()).toStdString() << std::endl;

        return false;
    }

    return true;
}

bool Mere::Lock::Config::checkInt(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    return Mere::Utils::StringUtils::isUInt(value);;
}

bool Mere::Lock::Config::checkBool(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    return Mere::Utils::StringUtils::isBoolean(value);
}

bool Mere::Lock::Config::checkColor(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    QColor color(QString::fromStdString(value));
    return color.isValid();
}

bool Mere::Lock::Config::checkImage(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    if (value.front() != '/')
        return false;

    if(Mere::Utils::FileUtils::isNotExist(value))
        return false;

    QPixmap pixmap(QString::fromStdString(value));

    return !pixmap.isNull();
}

bool Mere::Lock::Config::checkFont(const std::string &key) const
{
    std::string value;
    if(!checkKey(key, value)) return false;

    auto pos = value.find_first_of(' ');
    if (pos == std::string::npos)
        return false;

    auto font_size = value.substr(0, pos);
    if (!Utils::StringUtils::isUInt(font_size))
        return false;

    auto font_family = value.substr(pos + 1);
    if (font_family.empty()) return false;

    std::vector<std::string> families = Utils::StringUtils::split(font_family, ',');
    for(auto &family : families)
    {
        if (family.back() == '"') family.pop_back();
        if (family.front() == '"') family.erase(family.begin());;

        if(!std::all_of(family.begin(), family.end(), [](char const &c) {
            return std::isalnum(c) || c == ' ' || c == '-' || c == '_' || c == '[' || c == ']';
        })) return false;
    }

    return true;
}

bool Mere::Lock::Config::checkKey(const std::string &key, std::string &value) const
{
    bool set;
    value = this->get(key, &set);
    if (set)
    {
        value = Mere::Utils::StringUtils::trim(value);
        if (value.empty())
        {
            std::cout << qApp->translate("LockConfig", "LockConfigValueEmpty").arg(key.c_str()).toStdString() << std::endl;

            return false;
        }
    }

    return true;
}

QFont Mere::Lock::Config::font(const std::string &key, const QFont &font) const
{
    std::string value = this->get(key);
    value = Utils::StringUtils::trim(value);

    if (value.empty()) return font;

    auto pos = value.find_first_of(' ');
    if (pos == std::string::npos)
        return font;

    auto font_size = value.substr(0, pos);
    if (!Utils::StringUtils::isUInt(font_size))
        return font;

    QFont _font(font);
    _font.setPointSize(Mere::Utils::StringUtils::toInt(font_size));

    auto font_family = value.substr(pos + 1);
    if (font_family.empty()) return _font;

    QStringList list;
    std::vector<std::string> families = Utils::StringUtils::split(font_family, ',');
    for(auto &family : families)
    {
        // validate each font familt
        list.append(QString::fromStdString(family));
    }

    _font.setFamilies(list);

    return _font;
}

QColor Mere::Lock::Config::color(const std::string &key, const QColor &color) const
{
    std::string value = this->get(key);

    value = Utils::StringUtils::trim(value);
    if (value.empty()) return color;

    QColor _color(QString::fromStdString(value));
    if(!_color.isValid()) return color;

    return _color;
}

QVariant Mere::Lock::Config::background(const std::string &key, const QVariant &background) const
{
    std::string value = this->get(key);
    value = Utils::StringUtils::trim(value);
    if (value.empty()) return background;

    if (value.front() == '/')
    {
        QPixmap image(QString::fromStdString(value));
        if (!image.isNull()) return image;
    }

    QColor color(QString::fromStdString(value));
    if (color.isValid()) return color;

    return background;
}

bool Mere::Lock::Config::value(const std::string &key, const bool &default_value) const
{
    std::string value = this->get(key);

    value = Utils::StringUtils::trim(value);
    if (value.empty()) return default_value;

    return Mere::Utils::StringUtils::isTrue(value);
}

std::string Mere::Lock::Config::value(const std::string &key, const std::string &default_value) const
{
    std::string value = this->get(key);

    value = Utils::StringUtils::trim(value);
    if (value.empty()) value = default_value;

    return value;
}
