#ifndef MERE_LOCK_CONFIG_H
#define MERE_LOCK_CONFIG_H

#include "mere/config/kvconfig.h"

#include <QColor>
#include <QPixmap>

namespace Mere
{
namespace Lock
{

class Config : public Mere::Config::KVConfig
{
    explicit Config();
    explicit Config(const std::string &path, const Mere::Config::Spec::Strict &strict = Mere::Config::Spec::Strict::Soft);

public:
    int init();
    int validate() const;

    std::string password() const;
    void password(const std::string &password);

    unsigned int timeout() const;
    void timeout(unsigned int timeout);

    unsigned int attempts() const;
    bool checkUnlockAttempts() const;

    unsigned int blocktime() const;
    bool checkUnlockBlocktime() const;

    unsigned int promptTimeout() const;
    bool checkPromptTimeout() const;

    std::string screenBackground() const;
    bool checkScreenBackground() const;

    QColor screenBackgroundColor() const;
    bool checkScreenBackgroundColor() const;

    QPixmap screenBackgroundImage() const;
    bool checkScreenBackgroundImage() const;

    QColor screenMessageColor() const;
    bool checkScreenMessageColor() const;

    int screenMessageSize() const;
    bool checkScreenMessageSize() const;

    QColor blockMessageColor() const;
    bool checkBlockMessageColor() const;

    int blockMessageSize() const;
    bool checkBlockMessageSize() const;

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
    bool checkPromptBackgroundColor() const;
    bool checkPromptBackgroundImage() const;

    QColor promptBackgroundColor() const;
    QPixmap promptBackgroundImage() const;

    QColor promptMessageColor() const;
    bool checkPromptMessageColor() const;

    int promptMessageSize() const;
    bool checkPromptMessageSize() const;

    QColor screenElapseColor() const;
    bool checkScreenElapseColor() const;

    int screenElapseSize() const;
    bool checkScreenElapseSize() const;

    QColor blockTimeColor() const;
    bool checkBlockTimeColor() const;

    int blockTimeSize() const;
    bool checkBlockTimeSize() const;

    static Config* instance(const std::string &path = "", const Mere::Config::Spec::Strict &strict = Mere::Config::Spec::Strict::Soft)
    {
        static Config *instance = new Config(path, strict);

        return instance;
    }

private:
    bool checkBackground(const std::string &key) const;
    bool checkColor(const std::string &key, const std::string &color) const;

    bool checkLogo(const std::string &key) const;
    bool checkImage(const std::string &key, const std::string &path) const;

    bool checkInt(const std::string &key) const;
    bool checkBool(const std::string &key) const;
    bool checkKey(const std::string &key, std::string &value, bool &set) const;

    bool checkColor(const std::string &key) const;
    bool checkImage(const std::string &key) const;
};

}
}

#endif // MERE_LOCK_CONFIG_H
