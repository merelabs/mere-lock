#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>

Mere::Lock::Config::Config() :
    Mere::Lock::Config::Config("mere/lock.conf")
{
}

Mere::Lock::Config::Config(const std::string &path) :
    Mere::Config::KVConfig(path)
{
    load();
}

int Mere::Lock::Config::validate() const
{
    int err = 0;

    std::cout << "Checking configuration..." << std::endl;

    err = checkScreenLogo()            ? err : 1;
    err = checkScreenLogoShow()        ? err : 1;
    err = checkScreenBackground()      ? err : 1;
    err = checkScreenBackgroundColor() ? err : 1;
    err = checkScreenBackgroundImage() ? err : 1;
    err = checkScreenMessageColor()    ? err : 1;
    err = checkScreenMessageSize()     ? err : 1;

    err = checkPromptLogo()            ? err : 1;
    err = checkPromptLogoShow()        ? err : 1;
    err = checkPromptBackground()      ? err : 1;
    err = checkPromptBackgroundColor() ? err : 1;
    err = checkPromptBackgroundImage() ? err : 1;
    err = checkPromptMessageColor()    ? err : 1;
    err = checkPromptMessageSize()     ? err : 1;

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
    if (value.empty()) return 10;

    return std::stoi(value);
}

std::string Mere::Lock::Config::screenBackground() const
{
    std::string value = this->get("mere.lock.screen.background");
    if (value.empty()) return "#0B6623";

    return value;
}

bool Mere::Lock::Config::checkScreenBackground() const
{
    return checkBackground("mere.lock.screen.background");
}

QColor Mere::Lock::Config::screenBackgroundColor() const
{
    std::string value = this->get("mere.lock.screen.background.color");
    if (value.empty())
    {
        value = this->get("mere.lock.screen.background");
    }

    if (value.empty() || value.at(0) != '#')
        return QColor("#0B6623");

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor("#0B6623");

    return color;
}

bool Mere::Lock::Config::checkScreenBackgroundColor() const
{
    return checkColor("mere.lock.screen.background.color");
}

QPixmap Mere::Lock::Config::screenBackgroundImage() const
{
    std::string value = this->get("mere.lock.screen.background.image");
    if (value.empty())
    {
        value = this->get("mere.lock.screen.background");
    }

    if (value.empty() || value.at(0) != '/')
        return QPixmap();

    if(Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkScreenBackgroundImage() const
{
    return checkImage("mere.lock.screen.background.image");
}

QColor Mere::Lock::Config::screenMessageColor() const
{
    std::string value = this->get("mere.lock.screen.message.font.color");

    if (value.empty() || value.at(0) != '#')
        return QColor("#000");

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor("#000");

    return color;
}

bool Mere::Lock::Config::checkScreenMessageColor() const
{
    return checkColor("mere.lock.screen.message.font.color");
}

int Mere::Lock::Config::screenMessageSize() const
{
    std::string value = this->get("mere.lock.screen.message.font.size");
    if (value.empty()) return 10;

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkScreenMessageSize() const
{
    return checkInt("mere.lock.screen.message.font.size");
}

bool Mere::Lock::Config::logoshow() const
{
    std::string value = this->get("mere.lock.screen.logo.show");
    if (value.empty()) return true;

    return value == "true" || value == "yes" || value == "1" ;
}

bool Mere::Lock::Config::checkScreenLogoShow() const
{
    return checkBool("mere.lock.screen.logo.show");
}

std::string Mere::Lock::Config::logo() const
{
    std::string value = this->get("mere.lock.screen.logo");
    if (value.empty()) return "/usr/local/share/mere/lock/mere-logo.png";

    return value;
}

bool Mere::Lock::Config::checkScreenLogo() const
{
    return checkLogo("mere.lock.screen.logo");
}

bool Mere::Lock::Config::promptlogoshow() const
{
    std::string value = this->get("mere.lock.screen.prompt.logo.show");
    if (value.empty()) return true;

    return value == "true" || value == "yes" || value == "1" ;
}

bool Mere::Lock::Config::checkPromptLogoShow() const
{
    return checkBool("mere.lock.screen.prompt.logo.show");
}

std::string Mere::Lock::Config::promptlogo() const
{
    std::string value = this->get("mere.lock.screen.prompt.logo");
    if (value.empty()) return "/usr/local/share/mere/lock/freebsd-logo.png";

    return value;
}

bool Mere::Lock::Config::checkPromptLogo() const
{
    return checkLogo("mere.lock.screen.prompt.logo");
}

std::string Mere::Lock::Config::promptBackground() const
{
    std::string value = this->get("mere.lock.screen.prompt.background");
    if (value.empty()) return "#F9F9F9";

    return value;
}

bool Mere::Lock::Config::checkPromptBackground() const
{
    return checkBackground("mere.lock.screen.prompt.background");
}

QColor Mere::Lock::Config::promptBackgroundColor() const
{
    std::string value = this->get("mere.lock.screen.prompt.background.color");
    if (value.empty())
    {
        value = this->get("mere.lock.screen.prompt.background");
    }

    if (value.empty() || value.at(0) != '#')
        return QColor("#F9F9F9");

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor("#F9F9F9");

    return color;
}

bool Mere::Lock::Config::checkPromptBackgroundColor() const
{
    return checkColor("mere.lock.screen.prompt.background.color");
}

QPixmap Mere::Lock::Config::promptBackgroundImage() const
{
    std::string value = this->get("mere.lock.screen.prompt.background.image");
    if (value.empty())
    {
        value = this->get("mere.lock.screen.prompt.background");
    }

    if (value.empty() || value.at(0) != '/')
        return QPixmap();

    if(Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Mere::Lock::Config::checkPromptBackgroundImage() const
{
    return checkImage("mere.lock.screen.prompt.background.image");
}


QColor Mere::Lock::Config::promptMessageColor() const
{
    std::string value = this->get("mere.lock.screen.prompt.message.font.color");

    if (value.empty() || value.at(0) != '#')
        return QColor("#000");

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor("#000");

    return color;
}

bool Mere::Lock::Config::checkPromptMessageColor() const
{
    return checkColor("mere.lock.screen.prompt.message.font.color");
}

int Mere::Lock::Config::promptMessageSize() const
{
    std::string value = this->get("mere.lock.screen.prompt.message.font.size");
    if (value.empty()) return 10;

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkPromptMessageSize() const
{
    return checkInt("mere.lock.screen.prompt.message.font.size");
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

    std::cout << "  - " << key << " is set to invalid value - " << value << std::endl;
    return false;
}

bool Mere::Lock::Config::checkColor(const std::string &key, const std::string &color) const
{
    QColor c(QString::fromStdString(color));
    if (!c.isValid())
    {
        std::cout << "  - " << key << " is set to invalid color code - " << color << std::endl;
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
        std::cout << "  - " << key << " is set to invalid file path - " << path << std::endl;
        return false;
    }

    QPixmap pixmap(QString::fromStdString(path));
    if(pixmap.isNull())
    {
        std::cout << "  - " << key << " is set to invalid image path- " << path << std::endl;
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

    return Mere::Utils::StringUtils::toInt(value);
}

bool Mere::Lock::Config::checkBool(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return value == "true" || value == "false" || value == "yes" || value == "no" || value == "1" || value == "0";
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
            std::cout << "  - " << key << " is set to empty!" << std::endl;
            return false;
        }
    }

    return true;
}
