#ifndef MERE_LOCK_CONFIG_H
#define MERE_LOCK_CONFIG_H

#include "mere/config/kvconfig.h"

#include <QObject>

namespace Mere
{
namespace Lock
{

class Config : public Mere::Config::KVConfig
{
    explicit Config();
    explicit Config(const std::string &path);

public:
    int init();

    std::string password() const;
    void password(const std::string &password);

    unsigned int timeout() const;
    std::string background() const;

    bool logoshow() const;
    std::string logo() const;

    bool promptlogoshow() const;
    std::string promptlogo() const;

    std::string promptbackground() const;

    static Config* instance(const std::string &path = "")
    {
        static Config *instance = new Config(path);

        return instance;
    }
};

}
}

#endif // MERE_LOCK_CONFIG_H
