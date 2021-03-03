#include "config.h"

//Config::Config(QObject *parent) :
//    Mere::Config::Config("mere.display", parent)
//{
//}

Mere::Lock::Config::Config(const std::string &path, QObject *parent) :
    Mere::Config::Config(path, parent)
{
    m_properties = this->properties();
}

QVariant Mere::Lock::Config::get(const std::string &key) const
{
    auto result = m_properties.find(key);
    if (result != m_properties.end())
        return result->second;

    return QVariant();
}

void Mere::Lock::Config::set(const std::string &key, const QVariant &value)
{
    m_properties.insert({key, value});
}

unsigned int Mere::Lock::Config::timeout() const
{
    QVariant value = this->get("mere.lock.timeout");
    if (!value.isValid()) return 5;

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

std::string Mere::Lock::Config::promptshadow() const
{
    QVariant value = this->get("mere.lock.screen.prompt.shadow");
    if (!value.isValid()) return "#D3D3D3";

    return value.toString().toStdString();

}

std::string Mere::Lock::Config::promptbackground() const
{
    QVariant value = this->get("mere.lock.screen.prompt.background");
    if (!value.isValid()) return "#F9F9F9";

    return value.toString().toStdString();

}
