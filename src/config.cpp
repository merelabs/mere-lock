#include "config.h"

Mere::Lock::Config::Config() :
    Mere::Lock::Config::Config("mere/lock.conf")
{
}

Mere::Lock::Config::Config(const std::string &path) :
    Mere::Config::KVConfig(path)
{
    load();
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

std::string Mere::Lock::Config::background() const
{
    std::string value = this->get("mere.lock.screen.background");
    if (value.empty()) return "#0B6623";

    return value;
}

bool Mere::Lock::Config::logoshow() const
{
    std::string value = this->get("mere.lock.screen.logo.show");
    if (value.empty()) return true;

    return value.compare("false");
}

std::string Mere::Lock::Config::logo() const
{
    std::string value = this->get("mere.lock.screen.logo");
    if (value.empty()) return "/usr/local/share/mere/lock/mere-logo.png";

    return value;
}

bool Mere::Lock::Config::promptlogoshow() const
{
    std::string value = this->get("mere.lock.screen.prompt.logo.show");
    if (value.empty()) return true;

    return value.compare("false");
}

std::string Mere::Lock::Config::promptlogo() const
{
    std::string value = this->get("mere.lock.screen.prompt.logo");
    if (value.empty()) return "/usr/local/share/mere/lock/freebsd-logo.png";

    return value;
}

std::string Mere::Lock::Config::promptbackground() const
{
    std::string value = this->get("mere.lock.screen.prompt.background");
    if (value.empty()) return "#F9F9F9";

    return value;
}
