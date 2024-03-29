#include "unlocker.h"

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
