#include "config.h"

Mere::Lock::Config::Config(QObject *parent) :
    Mere::Config::KVConfig("mere/lock.conf", parent)
{
}

Mere::Lock::Config::Config(const std::string &path, QObject *parent) :
    Mere::Config::KVConfig(path, parent)
{
    load();
}

std::string Mere::Lock::Config::password() const
{
    QVariant value = this->get("mere.lock.password");
    if (!value.isValid()) return "";

    return value.toString().toStdString();
}
void Mere::Lock::Config::password(const std::string &password)
{
    this->set("mere.lock.password", password.c_str());
}

unsigned int Mere::Lock::Config::timeout() const
{
    QVariant value = this->get("mere.lock.timeout");
    if (!value.isValid()) return 10;

    return value.toUInt();
}

std::string Mere::Lock::Config::background() const
{
    QVariant value = this->get("mere.lock.screen.background");
    if (!value.isValid()) return "#0B6623";

    return value.toString().toStdString();
}

bool Mere::Lock::Config::logoshow() const
{
    QVariant value = this->get("mere.lock.screen.logo.show");
    if (!value.isValid()) return true;

    return value.toBool();
}

std::string Mere::Lock::Config::logo() const
{
    QVariant value = this->get("mere.lock.screen.logo");
    if (!value.isValid()) return "/usr/local/share/mere/lock/mere-logo.png";

    return value.toString().toStdString();
}

bool Mere::Lock::Config::promptlogoshow() const
{
    QVariant value = this->get("mere.lock.screen.prompt.logo.show");
    if (!value.isValid()) return true;

    return value.toBool();
}

std::string Mere::Lock::Config::promptlogo() const
{
    QVariant value = this->get("mere.lock.screen.prompt.logo");
    if (!value.isValid()) return "/usr/local/share/mere/lock/freebsd-logo.png";

    return value.toString().toStdString();
}

std::string Mere::Lock::Config::promptbackground() const
{
    QVariant value = this->get("mere.lock.screen.prompt.background");
    if (!value.isValid()) return "#F9F9F9";

    return value.toString().toStdString();
}
