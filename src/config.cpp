#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <QApplication>
#include <iostream>

static const std::string KEY_SCREEN_LOGO             = "mere.lock.screen.logo";
static const std::string VAL_SCREEN_LOGO             = "/usr/local/share/mere/lock/mere-logo.png";

static const std::string KEY_SCREEN_LOGO_SHOW        = "mere.lock.screen.logo.show";
static const std::string VAL_SCREEN_LOGO_SHOW        = "true";

static const std::string KEY_SCREEN_BACKGROUND       = "mere.lock.screen.background";
static const std::string VAL_SCREEN_BACKGROUND       = "#0B6623";

static const std::string KEY_SCREEN_BACKGROUND_COLOR = "mere.lock.screen.background.color";
static const std::string KEY_SCREEN_BACKGROUND_IMAGE = "mere.lock.screen.background.image";

static const std::string KEY_SCREEN_MESSAGE_SIZE     = "mere.lock.screen.message.font.size";
static const std::string VAL_SCREEN_MESSAGE_SIZE     = "10";

static const std::string KEY_SCREEN_MESSAGE_COLOR    = "mere.lock.screen.message.font.color";
static const std::string VAL_SCREEN_MESSAGE_COLOR    = "#000";

static const std::string KEY_PROMPT_TIMEOUT          = "mere.lock.screen.prompt.timeout";
static const std::string VAL_PROMPT_TIMEOUT          = "10";

static const std::string KEY_PROMPT_LOGO             = "mere.lock.screen.prompt.logo";
static const std::string VAL_PROMPT_LOGO             = "/usr/local/share/mere/lock/freebsd-logo.png";

static const std::string KEY_PROMPT_LOGO_SHOW        = "mere.lock.screen.prompt.logo.show";
static const std::string VAL_PROMPT_LOGO_SHOW        = "true";

static const std::string KEY_PROMPT_BACKGROUND       = "mere.lock.screen.prompt.background";
static const std::string VAL_PROMPT_BACKGROUND       = "#F9F9F9";

static const std::string KEY_PROMPT_BACKGROUND_COLOR = "mere.lock.screen.prompt.background.color";
static const std::string KEY_PROMPT_BACKGROUND_IMAGE = "mere.lock.screen.prompt.background.image";

static const std::string KEY_PROMPT_MESSAGE_SIZE     = "mere.lock.screen.prompt.message.font.size";
static const std::string VAL_PROMPT_MESSAGE_SIZE     = "10";

static const std::string KEY_PROMPT_MESSAGE_COLOR    = "mere.lock.screen.prompt.message.font.color";
static const std::string VAL_PROMPT_MESSAGE_COLOR    = "#000";

static const std::string KEY_LOCK_UNLOCK_ATTEMPTS    = "mere.lock.unlock.attempts";
static const std::string VAL_LOCK_UNLOCK_ATTEMPTS    = "3";

static const std::string KEY_LOCK_UNLOCK_BLOCKTIME    = "mere.lock.unlock.blocktime";
static const std::string VAL_LOCK_UNLOCK_BLOCKTIME    = "3";

static const std::string KEY_LOCK_SCREEN_ELAPSE_SIZE     = "mere.lock.screen.elapse.font.size";
static const std::string VAL_LOCK_SCREEN_ELAPSE_SIZE     = "92";

static const std::string KEY_LOCK_SCREEN_ELAPSE_COLOR    = "mere.lock.screen.elapse.font.color";
static const std::string VAL_LOCK_SCREEN_ELAPSE_COLOR    = "#FFF";

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
    int err = 0;

    std::cout << qApp->translate("LockConfig", "LockConfigValueCheck").toStdString() << std::endl,

    err = checkScreenLogo()            ? err : 1;
    err = checkScreenLogoShow()        ? err : 1;
    err = checkScreenBackground()      ? err : 1;
    err = checkScreenBackgroundColor() ? err : 1;
    err = checkScreenBackgroundImage() ? err : 1;
    err = checkScreenMessageColor()    ? err : 1;
    err = checkScreenMessageSize()     ? err : 1;
    err = checkScreenElapseColor()     ? err : 1;
    err = checkScreenElapseSize()      ? err : 1;

    err = checkPromptLogo()            ? err : 1;
    err = checkPromptLogoShow()        ? err : 1;
    err = checkPromptBackground()      ? err : 1;
    err = checkPromptBackgroundColor() ? err : 1;
    err = checkPromptBackgroundImage() ? err : 1;
    err = checkPromptMessageColor()    ? err : 1;
    err = checkPromptMessageSize()     ? err : 1;
    err = checkPromptTimeout()         ? err : 1;
    err = checkUnlockAttempts()        ? err : 1;
    err = checkUnlockBlocktime()       ? err : 1;

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
    if (value.empty()) return 0;

    return Mere::Utils::StringUtils::toInt(value);
}

void Mere::Lock::Config::timeout(unsigned int timeout)
{
    this->set("mere.lock.timeout", std::to_string(timeout));
}

unsigned int Mere::Lock::Config::attempts() const
{
    std::string value = this->get(KEY_LOCK_UNLOCK_ATTEMPTS);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_LOCK_UNLOCK_ATTEMPTS);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockAttempts() const
{
    return checkInt(KEY_LOCK_UNLOCK_ATTEMPTS);
}

unsigned int Mere::Lock::Config::blocktime() const
{
    std::string value = this->get(KEY_LOCK_UNLOCK_BLOCKTIME);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_LOCK_UNLOCK_BLOCKTIME);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockBlocktime() const
{
    return checkInt(KEY_LOCK_UNLOCK_BLOCKTIME);
}

unsigned int Mere::Lock::Config::promptTimeout() const
{
    std::string value = this->get(KEY_PROMPT_TIMEOUT);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_PROMPT_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkPromptTimeout() const
{
    return checkInt(KEY_PROMPT_TIMEOUT);
}

std::string Mere::Lock::Config::screenBackground() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND);
    if (value.empty()) return VAL_SCREEN_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkScreenBackground() const
{
    return checkBackground(KEY_SCREEN_BACKGROUND);
}

QColor Mere::Lock::Config::screenBackgroundColor() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND_COLOR);
    if (value.empty())
    {
        value = this->get(KEY_SCREEN_BACKGROUND);
    }

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_SCREEN_BACKGROUND));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_SCREEN_BACKGROUND));

    return color;
}

bool Mere::Lock::Config::checkScreenBackgroundColor() const
{
    return checkColor(KEY_SCREEN_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::screenBackgroundImage() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND_IMAGE);
    if (value.empty())
    {
        value = this->get(KEY_SCREEN_BACKGROUND);
    }

    if (value.empty() || value.at(0) != '/')
        return QPixmap();

    if(Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkScreenBackgroundImage() const
{
    return checkImage(KEY_SCREEN_BACKGROUND_IMAGE);
}

QColor Mere::Lock::Config::screenMessageColor() const
{
    std::string value = this->get(KEY_SCREEN_MESSAGE_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_SCREEN_MESSAGE_COLOR));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_SCREEN_MESSAGE_COLOR));

    return color;
}

bool Mere::Lock::Config::checkScreenMessageColor() const
{
    return checkColor(KEY_SCREEN_MESSAGE_COLOR);
}

int Mere::Lock::Config::screenMessageSize() const
{
    std::string value = this->get(KEY_SCREEN_MESSAGE_SIZE);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_SCREEN_MESSAGE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkScreenMessageSize() const
{
    return checkInt(KEY_SCREEN_MESSAGE_SIZE);
}

QColor Mere::Lock::Config::screenElapseColor() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_ELAPSE_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_SCREEN_ELAPSE_COLOR));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_LOCK_SCREEN_ELAPSE_COLOR));

    return color;
}

bool Mere::Lock::Config::checkScreenElapseColor() const
{
    return checkColor(KEY_LOCK_SCREEN_ELAPSE_COLOR);
}

int Mere::Lock::Config::screenElapseSize() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_ELAPSE_SIZE);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_LOCK_SCREEN_ELAPSE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkScreenElapseSize() const
{
    return checkInt(KEY_LOCK_SCREEN_ELAPSE_SIZE);
}

bool Mere::Lock::Config::logoshow() const
{
    std::string value = this->get(KEY_SCREEN_LOGO_SHOW);
    if (value.empty()) return true;

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkScreenLogoShow() const
{
    return checkBool(KEY_SCREEN_LOGO_SHOW);
}

std::string Mere::Lock::Config::logo() const
{
    std::string value = this->get(KEY_SCREEN_LOGO);
    if (value.empty()) return VAL_SCREEN_LOGO;

    return value;
}

bool Mere::Lock::Config::checkScreenLogo() const
{
    return checkLogo(KEY_SCREEN_LOGO);
}

bool Mere::Lock::Config::promptlogoshow() const
{
    std::string value = this->get(KEY_PROMPT_LOGO_SHOW);
    if (value.empty()) return true;

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkPromptLogoShow() const
{
    return checkBool(KEY_PROMPT_LOGO_SHOW);
}

std::string Mere::Lock::Config::promptlogo() const
{
    std::string value = this->get(KEY_PROMPT_LOGO);
    if (value.empty()) return VAL_PROMPT_LOGO;

    return value;
}

bool Mere::Lock::Config::checkPromptLogo() const
{
    return checkLogo(KEY_PROMPT_LOGO);
}

std::string Mere::Lock::Config::promptBackground() const
{
    std::string value = this->get(KEY_PROMPT_BACKGROUND);
    if (value.empty()) return VAL_PROMPT_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkPromptBackground() const
{
    return checkBackground(KEY_PROMPT_BACKGROUND);
}

QColor Mere::Lock::Config::promptBackgroundColor() const
{
    std::string value = this->get(KEY_PROMPT_BACKGROUND_COLOR);
    if (value.empty())
    {
        value = this->get(KEY_PROMPT_BACKGROUND);
    }

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_PROMPT_BACKGROUND));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_PROMPT_BACKGROUND));

    return color;
}

bool Mere::Lock::Config::checkPromptBackgroundColor() const
{
    return checkColor(KEY_PROMPT_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::promptBackgroundImage() const
{
    std::string value = this->get(KEY_PROMPT_BACKGROUND_IMAGE);
    if (value.empty())
    {
        value = this->get(KEY_PROMPT_BACKGROUND);
    }

    if (value.empty() || value.at(0) != '/')
        return QPixmap();

    if(Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptBackgroundImage() const
{
    return checkImage(KEY_PROMPT_BACKGROUND_IMAGE);
}

QColor Mere::Lock::Config::promptMessageColor() const
{
    std::string value = this->get(KEY_PROMPT_MESSAGE_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_PROMPT_MESSAGE_COLOR));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_PROMPT_MESSAGE_COLOR));

    return color;
}

bool Mere::Lock::Config::checkPromptMessageColor() const
{
    return checkColor(KEY_PROMPT_MESSAGE_COLOR);
}

int Mere::Lock::Config::promptMessageSize() const
{
    std::string value = this->get(KEY_PROMPT_MESSAGE_SIZE);
    if (value.empty()) return Mere::Utils::StringUtils::toInt(VAL_PROMPT_MESSAGE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkPromptMessageSize() const
{
    return checkInt(KEY_PROMPT_MESSAGE_SIZE);
}

bool Mere::Lock::Config::checkBackground(const std::string &key) const
{
    bool set =false;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

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
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

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
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return Mere::Utils::StringUtils::isUInt(value);;
}

bool Mere::Lock::Config::checkBool(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return Mere::Utils::StringUtils::isBoolean(value);
}

bool Mere::Lock::Config::checkColor(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    QColor color(QString::fromStdString(value));
    return color.isValid();
}

bool Mere::Lock::Config::checkImage(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    if (value.at(0) != '/')
        return false;

    if(Mere::Utils::FileUtils::isNotExist(value))
        return false;

    QPixmap pixmap(QString::fromStdString(value));

    return !pixmap.isNull();
}

bool Mere::Lock::Config::checkKey(const std::string &key, std::string &value, bool &set) const
{
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
