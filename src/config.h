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
    int validate() const;

    std::string password() const;
    void password(const std::string &password);

    unsigned int timeout() const;

    std::string screenBackground() const;
    bool checkScreenBackground() const;

    bool logoshow() const;
    bool checkScreenLogoShow() const;

    std::string logo() const;
    bool checkScreenLogo() const;

    bool promptlogoshow() const;
    bool checkPromptLogoShow() const;

    std::string promptlogo() const;
    bool checkPromptLogo() const;

    std::string promptBackground() const;
    bool checkPromptBackground() const;

    static Config* instance(const std::string &path = "")
    {
        static Config *instance = new Config(path);

        return instance;
    }

private:
    bool checkBackground(const std::string &key) const;
    bool checkColor(const std::string &key, const std::string &color) const;

    bool checkLogo(const std::string &key) const;
    bool checkImage(const std::string &key, const std::string &path) const;

    bool checkBool(const std::string &key) const;
    bool checkKey(const std::string &key, std::string &value, bool &set) const;
};

}
}

#endif // MERE_LOCK_CONFIG_H
