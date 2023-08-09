#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>

#include <QApplication>

//
// Prompt Screen
//

//----
static const std::string KEY_LOCK_PROMPT_BACKGROUND         = "mere.lock.prompt.background";
static const std::string VAL_LOCK_PROMPT_BACKGROUND         = "#FFF";

static const std::string KEY_LOCK_PROMPT_BACKGROUND_COLOR   = "mere.lock.prompt.background.color";
static const std::string KEY_LOCK_PROMPT_BACKGROUND_IMAGE   = "mere.lock.prompt.background.image";

static const std::string KEY_LOCK_PROMPT_LOGO               = "mere.lock.prompt.logo";
static const std::string VAL_LOCK_PROMPT_LOGO               = "/usr/local/share/mere/lock/freebsd-logo.png";

static const std::string KEY_LOCK_PROMPT_LOGO_SHOW          = "mere.lock.prompt.logo.show";
static const std::string VAL_LOCK_PROMPT_LOGO_SHOW          = "true";

static const std::string KEY_LOCK_PROMPT_MESSAGE_COLOR      = "mere.lock.prompt.message.font.color";
static const std::string VAL_LOCK_PROMPT_MESSAGE_COLOR      = "#000";

static const std::string KEY_LOCK_PROMPT_MESSAGE_SIZE       = "mere.lock.prompt.message.font.size";
static const std::string VAL_LOCK_PROMPT_MESSAGE_SIZE       = "10";

static const std::string KEY_LOCK_PROMPT_TIMEOUT            = "mere.lock.prompt.timeout";
static const std::string VAL_LOCK_PROMPT_TIMEOUT            = "15";

static const std::string KEY_LOCK_PROMPT_TIMEBAR_COLOR      = "mere.lock.prompt.timebar.color";
static const std::string VAL_LOCK_PROMPT_TIMEBAR_COLOR      = "#FFF";

//----

//
// Lock Screen
//
static const std::string KEY_LOCK_SCREEN_BACKGROUND                 = "mere.lock.screen.background";
static const std::string VAL_LOCK_SCREEN_BACKGROUND                 = "#0B6623";

static const std::string KEY_LOCK_SCREEN_BACKGROUND_COLOR           = "mere.lock.screen.background.color";
static const std::string KEY_LOCK_SCREEN_BACKGROUND_IMAGE           = "mere.lock.screen.background.image";

static const std::string KEY_LOCK_SCREEN_TIME_FONT_COLOR            = "mere.lock.screen.elapse.font.color";
static const std::string VAL_LOCK_SCREEN_TIME_FONT_COLOR            = "#FFF";

static const std::string KEY_LOCK_SCREEN_TIME_FONT_SIZE             = "mere.lock.screen.elapse.font.size";
static const std::string VAL_LOCK_SCREEN_TIME_FONT_SIZE             = "92";

static const std::string KEY_LOCK_SCREEN_MESSAGE_FONT_COLOR         = "mere.lock.screen.message.font.color";
static const std::string VAL_LOCK_SCREEN_MESSAGE_FONT_COLOR         = "#000";

static const std::string KEY_LOCK_SCREEN_MESSAGE_FONT_SIZE          = "mere.lock.screen.message.font.size";
static const std::string VAL_LOCK_SCREEN_MESSAGE_FONT_SIZE          = "10";

//
// Lock Screeb Prompt
//
static const std::string KEY_LOCK_SCREEN_PROMPT_BACKGROUND        = "mere.lock.screen.prompt.background";
static const std::string VAL_LOCK_SCREEN_PROMPT_BACKGROUND        = "#89CFF0"; //VAL_LOCK_PROMPT_BACKGROUND;

static const std::string KEY_LOCK_SCREEN_PROMPT_BACKGROUND_COLOR  = "mere.lock.screen.prompt.background.color";
static const std::string KEY_LOCK_SCREEN_PROMPT_BACKGROUND_IMAGE  = "mere.lock.screen.prompt.background.image";

static const std::string KEY_LOCK_SCREEN_PROMPT_LOGO              = "mere.lock.screen.prompt.logo";
static const std::string VAL_LOCK_SCREEN_PROMPT_LOGO              = "/usr/local/share/mere/lock/freebsd-logo.png";

static const std::string KEY_LOCK_SCREEN_PROMPT_LOGO_SHOW         = "mere.lock.screen.prompt.logo.show";
static const std::string VAL_LOCK_SCREEN_PROMPT_LOGO_SHOW         = "true";

static const std::string KEY_LOCK_SCREEN_PROMPT_MESSAGE_COLOR     = "mere.lock.screen.prompt.message.font.color";
static const std::string VAL_LOCK_SCREEN_PROMPT_MESSAGE_COLOR     = "#000";

static const std::string KEY_LOCK_SCREEN_PROMPT_MESSAGE_SIZE      = "mere.lock.screen.prompt.message.font.size";
static const std::string VAL_LOCK_SCREEN_PROMPT_MESSAGE_SIZE      = "10";

static const std::string KEY_LOCK_SCREEN_PROMPT_TIMEOUT           = "mere.lock.screen.prompt.timeout";
static const std::string VAL_LOCK_SCREEN_PROMPT_TIMEOUT           = "15";

//
// Block Screen
//
static const std::string KEY_BLOCK_SCREEN_BACKGROUND                = "mere.lock.block.screen.background";
static const std::string VAL_BLOCK_SCREEN_BACKGROUND                = "#FF0000";

static const std::string KEY_BLOCK_SCREEN_BACKGROUND_COLOR          = "mere.lock.block.screen.background.color";
static const std::string KEY_BLOCK_SCREEN_BACKGROUND_IMAGE          = "mere.lock.block.screen.background.image";

static const std::string KEY_BLOCK_SCREEN_TIME_FONT_COLOR           = "mere.lock.block.screen.time.font.color";
static const std::string VAL_BLOCK_SCREEN_TIME_FONT_COLOR           = "#D6ED17";

static const std::string KEY_BLOCK_SCREEN_TIME_FONT_SIZE            = "mere.lock.block.screen.time.font.size";
static const std::string VAL_BLOCK_SCREEN_TIME_FONT_SIZE            = "92";

static const std::string KEY_BLOCK_SCREEN_MESSAGE_FONT_COLOR        = "mere.lock.block.screen.message.font.color";
static const std::string VAL_BLOCK_SCREEN_MESSAGE_FONT_COLOR        = "#000";

static const std::string KEY_BLOCK_SCREEN_MESSAGE_FONT_SIZE         = "mere.lock.block.screen.message.font.size";
static const std::string VAL_BLOCK_SCREEN_MESSAGE_FONT_SIZE         = "10";

static const std::string KEY_LOCK_BLOCK_TIMEOUT                     = "mere.lock.block.timeout";
static const std::string VAL_LOCK_BLOCK_TIMEOUT                     = "2";

//
// Unlock Screen
//
static const std::string KEY_UNLOCK_SCREEN_BACKGROUND               = "mere.lock.unlock.screen.background";
static const std::string VAL_UNLOCK_SCREEN_BACKGROUND               = "#0B6623";

static const std::string KEY_UNLOCK_SCREEN_BACKGROUND_COLOR         = "mere.lock.unlock.screen.background.color";
static const std::string KEY_UNLOCK_SCREEN_BACKGROUND_IMAGE         = "mere.lock.unlock.screen.background.image";

//
// unlock prompt screen
//
static const std::string KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND        = "mere.lock.unlock.screen.prompt.background";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_BACKGROUND        = "#FFF";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_COLOR  = "mere.lock.unlock.screen.prompt.background.color";
static const std::string KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_IMAGE  = "mere.lock.unlock.screen.prompt.background.image";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_LOGO              = "mere.lock.unlock.screen.prompt.logo";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_LOGO              = "/usr/local/share/mere/lock/freebsd-logo.png";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_LOGO_SHOW         = "mere.lock.unlock.screen.prompt.logo.show";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_LOGO_SHOW         = "true";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_COLOR     = "mere.lock.unlock.screen.prompt.message.font.color";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_MESSAGE_COLOR     = "#000";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_SIZE      = "mere.lock.unlock.screen.prompt.message.font.size";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_MESSAGE_SIZE      = "10";

static const std::string KEY_UNLOCK_SCREEN_PROMPT_TIMEOUT           = "mere.lock.unlock.screen.prompt.timeout";
static const std::string VAL_UNLOCK_SCREEN_PROMPT_TIMEOUT           = "15";

//
// Generic
//
static const std::string KEY_UNLOCK_ATTEMPTS                        = "mere.lock.unlock.attempts";
static const std::string VAL_UNLOCK_ATTEMPTS                        = "3";

static const std::string KEY_LOCK_LOGO                              = "mere.lock.logo";
static const std::string VAL_LOCK_LOGO                              = "/usr/local/share/mere/lock/mere-logo.png";

static const std::string KEY_LOCK_LOGO_SHOW                         = "mere.lock.logo.show";
static const std::string VAL_LOCK_LOGO_SHOW                         = "true";

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

    err = checkPromptBackground()                   ? err : 1;
    err = checkPromptBackgroundColor()              ? err : 1;
    err = checkPromptBackgroundImage()              ? err : 1;
    err = checkPromptLogo()                         ? err : 1;
    err = checkPromptLogoShow()                     ? err : 1;
    err = checkPromptMessageColor()                 ? err : 1;
    err = checkPromptMessageSize()                  ? err : 1;
    err = checkPromptTimeout()                      ? err : 1;
    err = checkPromptTimebarColor()                 ? err : 1;

    err = checkLockScreenBackground()               ? err : 1;
    err = checkLockScreenBackgroundColor()          ? err : 1;
    err = checkLockScreenBackgroundImage()          ? err : 1;
    err = checkLockScreenTimeFontColor()            ? err : 1;
    err = checkLockScreenTimeFontSize()             ? err : 1;
    err = checkLockScreenMessageFontColor()         ? err : 1;
    err = checkLockScreenMessageFontSize()          ? err : 1;
    err = checkLockScreenLogo()                     ? err : 1;
    err = checkLockScreenLogoShow()                 ? err : 1;
    err = checkLockScreenPromptBackgroundImage()    ? err : 1;
    err = checkLockScreenPromptLogo()               ? err : 1;
    err = checkLockScreenPromptLogoShow()           ? err : 1;
    err = checkLockScreenPromptMessageColor()       ? err : 1;
    err = checkLockScreenPromptMessageSize()        ? err : 1;
    err = checkLockScreenPromptTimeout()            ? err : 1;

    err = checkBlockScreenBackground()              ? err : 1;
    err = checkBlockScreenBackgroundColor()         ? err : 1;
    err = checkBlockScreenBackgroundImage()         ? err : 1;
    err = checkBlockScreenTimeFontColor()           ? err : 1;
    err = checkBlockScreenTimeFontSize()            ? err : 1;
    err = checkBlockScreenMessageFontColor()        ? err : 1;
    err = checkBlockScreenMessageFontSize()         ? err : 1;
    err = checkBlockTimeout()                       ? err : 1;
    err = checkUnlockScreenPromptBackground()       ? err : 1;
    err = checkUnlockScreenPromptBackgroundColor()  ? err : 1;

    err = checkUnlockScreenPromptBackgroundImage()  ? err : 1;
    err = checkUnlockScreenPromptLogo()             ? err : 1;
    err = checkUnlockScreenPromptLogoShow()         ? err : 1;
    err = checkUnlockScreenPromptMessageColor()     ? err : 1;
    err = checkUnlockScreenPromptMessageSize()      ? err : 1;

    err = checkUnlockScreenPromptTimeout()          ? err : 1;
    err = checkUnlockAttempts()                     ? err : 1;

    if(err)
        std::cout << qApp->translate("LockConfig", "LockConfigValueCheckFailed").toStdString() << std::endl;

    return err;
}

bool Mere::Lock::Config::ask() const
{
    return this->get("mere.lock.password.ask") == "1";
}

void Mere::Lock::Config::ask(bool ask)
{
    this->set("mere.lock.password.ask", ask ? "1" : "0");
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

std::string Mere::Lock::Config::promptBackground() const
{
    // see if it is set in the config, use default otherwise
    std::string value = this->get(KEY_LOCK_PROMPT_BACKGROUND);
    if (value.empty()) return VAL_LOCK_PROMPT_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkPromptBackground() const
{
    return checkBackground(KEY_LOCK_PROMPT_BACKGROUND);
}

QColor Mere::Lock::Config::promptBackgroundColor() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        value = promptBackground();

    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptBackgroundColor() const
{
    return checkColor(KEY_LOCK_PROMPT_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::promptBackgroundImage() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = promptBackground();

    if(value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptBackgroundImage() const
{
    return checkImage(KEY_LOCK_PROMPT_BACKGROUND_IMAGE);
}

QPixmap Mere::Lock::Config::promptLogo() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_LOGO);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap(QString::fromStdString(VAL_LOCK_PROMPT_LOGO));

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptLogo() const
{
    return checkLogo(KEY_LOCK_PROMPT_LOGO);
}

bool Mere::Lock::Config::promptLogoShow() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_LOGO_SHOW);
    if (value.empty()) return Mere::Utils::StringUtils::isTrue(VAL_LOCK_PROMPT_LOGO_SHOW);

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkPromptLogoShow() const
{
    return checkBool(KEY_LOCK_PROMPT_LOGO_SHOW);
}

QColor Mere::Lock::Config::promptMessageColor() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_MESSAGE_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_PROMPT_MESSAGE_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptMessageColor() const
{
    return checkColor(KEY_LOCK_PROMPT_MESSAGE_COLOR);
}

int Mere::Lock::Config::promptMessageSize() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_MESSAGE_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_PROMPT_MESSAGE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkPromptMessageSize() const
{
    return checkInt(KEY_LOCK_PROMPT_MESSAGE_SIZE);
}

unsigned int Mere::Lock::Config::promptTimeout() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_TIMEOUT);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_PROMPT_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkPromptTimeout() const
{
    return checkInt(KEY_LOCK_PROMPT_TIMEOUT);
}

QColor Mere::Lock::Config::promptTimebarColor() const
{
    std::string value = this->get(KEY_LOCK_PROMPT_TIMEBAR_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_PROMPT_TIMEBAR_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptTimebarColor() const
{
    return checkColor(KEY_LOCK_PROMPT_TIMEBAR_COLOR);
}

std::string Mere::Lock::Config::lockScreenBackground() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_BACKGROUND);
    if (value.empty()) return VAL_LOCK_SCREEN_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkLockScreenBackground() const
{
    return checkBackground(KEY_LOCK_SCREEN_BACKGROUND);
}

QColor Mere::Lock::Config::lockScreenBackgroundColor() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        value = unlockScreenBackground();

    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenBackgroundColor() const
{
    return checkColor(KEY_LOCK_SCREEN_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::lockScreenBackgroundImage() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = unlockScreenBackground();

    if(value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenBackgroundImage() const
{
    return checkImage(KEY_LOCK_SCREEN_BACKGROUND_IMAGE);
}

QColor Mere::Lock::Config::lockScreenTimeFontColor() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_TIME_FONT_COLOR);
    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_SCREEN_TIME_FONT_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenTimeFontColor() const
{
    return checkColor(KEY_LOCK_SCREEN_TIME_FONT_COLOR);
}

int Mere::Lock::Config::lockScreenTimeFontSize() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_TIME_FONT_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_SCREEN_TIME_FONT_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkLockScreenTimeFontSize() const
{
    return checkInt(KEY_LOCK_SCREEN_TIME_FONT_SIZE);
}

QColor Mere::Lock::Config::lockScreenMessageFontColor() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_MESSAGE_FONT_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_SCREEN_MESSAGE_FONT_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenMessageFontColor() const
{
    return checkColor(KEY_LOCK_SCREEN_MESSAGE_FONT_COLOR);
}

int Mere::Lock::Config::lockScreenMessageFontSize() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_MESSAGE_FONT_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_SCREEN_MESSAGE_FONT_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkLockScreenMessageFontSize() const
{
    return checkInt(KEY_LOCK_SCREEN_MESSAGE_FONT_SIZE);
}

std::string Mere::Lock::Config::lockScreenPromptBackground() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_BACKGROUND);
    if (value.empty()) return VAL_LOCK_SCREEN_PROMPT_BACKGROUND;;

    return value;
}

bool Mere::Lock::Config::checkLockScreenPromptBackground() const
{
    return checkBackground(KEY_LOCK_SCREEN_PROMPT_BACKGROUND);
}

QColor Mere::Lock::Config::lockScreenPromptBackgroundColor() const
{
    // check if it is set in own key
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        // grab the value from background key
        value = lockScreenPromptBackground();

    // check if background key's value is valid
    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenPromptBackgroundColor() const
{
    return checkColor(KEY_LOCK_SCREEN_PROMPT_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::lockScreenPromptBackgroundImage() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = lockScreenPromptBackground();

    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenPromptBackgroundImage() const
{
    return checkImage(KEY_LOCK_SCREEN_PROMPT_BACKGROUND_IMAGE);
}

QPixmap Mere::Lock::Config::lockScreenPromptLogo() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_LOGO);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap(QString::fromStdString(VAL_LOCK_SCREEN_PROMPT_LOGO));

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenPromptLogo() const
{
    return checkLogo(KEY_LOCK_SCREEN_PROMPT_LOGO);
}

bool Mere::Lock::Config::lockScreenPromptLogoShow() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_LOGO_SHOW);
    if (value.empty()) return Mere::Utils::StringUtils::isTrue(VAL_LOCK_SCREEN_PROMPT_LOGO_SHOW);

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkLockScreenPromptLogoShow() const
{
    return checkBool(KEY_LOCK_SCREEN_PROMPT_LOGO_SHOW);
}

QColor Mere::Lock::Config::lockScreenPromptMessageColor() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_MESSAGE_COLOR);
    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_LOCK_SCREEN_PROMPT_MESSAGE_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkLockScreenPromptMessageColor() const
{
    return checkColor(KEY_LOCK_SCREEN_PROMPT_MESSAGE_COLOR);
}

int Mere::Lock::Config::lockScreenPromptMessageSize() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_MESSAGE_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_SCREEN_PROMPT_MESSAGE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkLockScreenPromptMessageSize() const
{
    return checkInt(KEY_LOCK_SCREEN_PROMPT_MESSAGE_SIZE);
}

unsigned int Mere::Lock::Config::lockScreenPromptTimeout() const
{
    std::string value = this->get(KEY_LOCK_SCREEN_PROMPT_TIMEOUT);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_LOCK_SCREEN_PROMPT_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkLockScreenPromptTimeout() const
{
    return checkInt(KEY_LOCK_SCREEN_PROMPT_TIMEOUT);
}
//--

std::string Mere::Lock::Config::blockScreenBackground() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_BACKGROUND);
    if (value.empty()) return VAL_BLOCK_SCREEN_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkBlockScreenBackground() const
{
    return checkBackground(KEY_BLOCK_SCREEN_BACKGROUND);
}

QColor Mere::Lock::Config::blockScreenBackgroundColor() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        value = blockScreenBackground();

    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkBlockScreenBackgroundColor() const
{
    return checkColor(KEY_BLOCK_SCREEN_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::blockScreenBackgroundImage() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = blockScreenBackground();

    if(value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkBlockScreenBackgroundImage() const
{
    return checkImage(KEY_BLOCK_SCREEN_BACKGROUND_IMAGE);
}

QColor Mere::Lock::Config::blockScreenTimeFontColor() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_TIME_FONT_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_BLOCK_SCREEN_TIME_FONT_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkBlockScreenTimeFontColor() const
{
    return checkColor(KEY_BLOCK_SCREEN_TIME_FONT_COLOR);
}

int Mere::Lock::Config::blockScreenTimeFontSize() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_TIME_FONT_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_BLOCK_SCREEN_TIME_FONT_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkBlockScreenTimeFontSize() const
{
    return checkInt(KEY_BLOCK_SCREEN_TIME_FONT_SIZE);
}

QColor Mere::Lock::Config::blockScreenMessageFontColor() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_MESSAGE_FONT_COLOR);

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_BLOCK_SCREEN_MESSAGE_FONT_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkBlockScreenMessageFontColor() const
{
    return checkColor(KEY_BLOCK_SCREEN_MESSAGE_FONT_COLOR);
}

int Mere::Lock::Config::blockScreenMessageFontSize() const
{
    std::string value = this->get(KEY_BLOCK_SCREEN_MESSAGE_FONT_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_BLOCK_SCREEN_MESSAGE_FONT_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkBlockScreenMessageFontSize() const
{
    return checkInt(KEY_BLOCK_SCREEN_MESSAGE_FONT_SIZE);
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

std::string Mere::Lock::Config::unlockScreenBackground() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_BACKGROUND);
    if (value.empty()) return VAL_UNLOCK_SCREEN_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkUnlockScreenBackground() const
{
    return checkBackground(KEY_UNLOCK_SCREEN_BACKGROUND);
}

QColor Mere::Lock::Config::unlockScreenBackgroundColor() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        value = unlockScreenBackground();

    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkUnlockScreenBackgroundColor() const
{
    return checkColor(KEY_UNLOCK_SCREEN_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::unlockScreenBackgroundImage() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = unlockScreenBackground();

    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkUnlockScreenBackgroundImage() const
{
    return checkImage(KEY_UNLOCK_SCREEN_BACKGROUND_IMAGE);
}

std::string Mere::Lock::Config::unlockScreenPromptBackground() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND);
    if (value.empty()) return VAL_UNLOCK_SCREEN_PROMPT_BACKGROUND;

    return value;
}

bool Mere::Lock::Config::checkUnlockScreenPromptBackground() const
{
    return checkBackground(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND);
}

QColor Mere::Lock::Config::unlockScreenPromptBackgroundColor() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_COLOR);
    if (value.empty() || value.at(0) != '#')
        value = unlockScreenPromptBackground();

    if (value.empty() || value.at(0) != '#')
        return QColor();

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkUnlockScreenPromptBackgroundColor() const
{
    return checkColor(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_COLOR);
}

QPixmap Mere::Lock::Config::unlockScreenPromptBackgroundImage() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_IMAGE);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        value = unlockScreenPromptBackground();

    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkUnlockScreenPromptBackgroundImage() const
{
    return checkImage(KEY_UNLOCK_SCREEN_PROMPT_BACKGROUND_IMAGE);
}

QPixmap Mere::Lock::Config::unlockScreenPromptLogo() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_LOGO);
    if (value.empty() || Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap(QString::fromStdString(VAL_UNLOCK_SCREEN_PROMPT_LOGO));

    return QPixmap(QString::fromStdString(value));;
}

bool Mere::Lock::Config::checkUnlockScreenPromptLogo() const
{
    return checkLogo(KEY_UNLOCK_SCREEN_PROMPT_LOGO);
}

bool Mere::Lock::Config::unlockScreenPromptLogoShow() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_LOGO_SHOW);
    if (value.empty()) return Mere::Utils::StringUtils::isTrue(VAL_UNLOCK_SCREEN_PROMPT_LOGO_SHOW);

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Mere::Lock::Config::checkUnlockScreenPromptLogoShow() const
{
    return checkBool(KEY_UNLOCK_SCREEN_PROMPT_LOGO_SHOW);
}

QColor Mere::Lock::Config::unlockScreenPromptMessageColor() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_COLOR);
    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_UNLOCK_SCREEN_PROMPT_MESSAGE_COLOR));

    return QColor(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkUnlockScreenPromptMessageColor() const
{
    return checkColor(KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_COLOR);
}

int Mere::Lock::Config::unlockScreenPromptMessageSize() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_SIZE);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_UNLOCK_SCREEN_PROMPT_MESSAGE_SIZE);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockScreenPromptMessageSize() const
{
    return checkInt(KEY_UNLOCK_SCREEN_PROMPT_MESSAGE_SIZE);
}

unsigned int Mere::Lock::Config::unlockScreenPromptTimeout() const
{
    std::string value = this->get(KEY_UNLOCK_SCREEN_PROMPT_TIMEOUT);
    if (value.empty() || !Mere::Utils::StringUtils::isUInt(value))
        return Mere::Utils::StringUtils::toInt(VAL_UNLOCK_SCREEN_PROMPT_TIMEOUT);

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkUnlockScreenPromptTimeout() const
{
    return checkInt(KEY_UNLOCK_SCREEN_PROMPT_TIMEOUT);
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
    std::string value = this->get(KEY_LOCK_LOGO);
    if (value.empty()) return VAL_LOCK_LOGO;

    return value;
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
