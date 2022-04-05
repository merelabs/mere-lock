#ifndef LOCKAPP_H
#define LOCKAPP_H

#include "locker.h"
#include "config.h"

#include "mere/widgets/defaultapp.h"

namespace Mere
{
    namespace Lock
    {
        #ifdef APP_CODE
        const std::string AppCode   = APP_CODE;
        #else
        const std::string AppCode   = "lock";
        #endif

        #ifdef APP_NAME
        const std::string AppName   = APP_NAME;
        #else
        const std::string AppName   = "mere-lock";
        #endif

        #ifdef APP_VERSION
        const std::string AppVersion= APP_VERSION;
        #else
        const std::string AppVersion= "0.0.0b";
        #endif
    }
}

class LockApp : public Mere::Widgets::DefaultApp
{
    Q_OBJECT
public:
    ~LockApp();
    LockApp(int &argc, char **argv);
    int start();

private:
    Mere::Lock::Locker *m_locker;
    Mere::Lock::Config *m_config;
};
#endif // LOCKAPP_H
