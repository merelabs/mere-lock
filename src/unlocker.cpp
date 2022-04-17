#include "unlocker.h"
#include "config.h"

#include "mere/auth/service.h"
#include "mere/utils/stringutils.h"

int Mere::Lock::Unlocker::InProgress = 1;
Mere::Lock::Unlocker::Unlocker(QObject *parent)
    : QObject(parent),
      m_state(0),
      m_attempt(0)
{
}

int Mere::Lock::Unlocker::state()
{
    return m_state;
}

void Mere::Lock::Unlocker::state(unsigned int state)
{
    m_state = state;
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
