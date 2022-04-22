#include "unlocker.h"
#include "config.h"

#include "mere/auth/service.h"
#include "mere/utils/stringutils.h"

Mere::Lock::Unlocker::Unlocker(QObject *parent)
    : QObject(parent),
      m_attempt(0)
{
}

unsigned int Mere::Lock::Unlocker::attempt()
{
    return m_attempt;
}

void Mere::Lock::Unlocker::attempt(unsigned int attempt)
{
    m_attempt = attempt;
}

bool Mere::Lock::Unlocker::verify(const std::string &secret)
{
    // increase the attempt even it is with empty password
    ++m_attempt;

    if (Mere::Utils::StringUtils::isBlank(secret))
        return false;

    auto config = Mere::Lock::Config::instance();

    std::string password = config->password();
    if (Mere::Utils::StringUtils::isNotBlank(password) && secret == password)
        return true;

    Mere::Auth::Service service;
    return service.verify(secret);
}
