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
    QVariant value = this->get("mere.lock.background");
    if (!value.isValid()) return "#0B6623";

    return value.toString().toStdString();
}
