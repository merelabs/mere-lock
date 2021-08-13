#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>
#include <QColor>
#include <QPixmap>

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

    err = checkScreenLogo()       ? err : 1;
    err = checkScreenLogoShow()   ? err : 1;
    err = checkScreenBackground() ? err : 1;

    err = checkPromptLogo()       ? err : 1;
    err = checkPromptLogoShow()   ? err : 1;
    err = checkPromptBackground() ? err : 1;

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

bool Mere::Lock::Config::logoshow() const
{
    std::string value = this->get("mere.lock.screen.logo.show");
    if (value.empty()) return true;

    return value.compare("false");
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

    return value.compare("false");
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

bool Mere::Lock::Config::checkBool(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return value == "true" || value == "false" || value == "yes" || value == "no" || value == "1" || value == "0";
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
