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

    std::string lockScreenBackground() const;
    bool checkLockScreenBackground() const;

    QColor lockScreenBackgroundColor() const;
    bool checkLockScreenBackgroundColor() const;

    QPixmap lockScreenBackgroundImage() const;
    bool checkLockScreenBackgroundImage() const;

    QColor lockScreenTimeColor() const;
    bool checkLockScreenTimeColor() const;

    int lockScreenTimeSize() const;
    bool checkLockScreenTimeSize() const;

    QColor lockScreenMessageColor() const;
    bool checkLockScreenMessageColor() const;

    int lockScreenMessageSize() const;
    bool checkLockScreenMessageSize() const;

    std::string blockScreenBackground() const;
    bool checkBlockScreenBackground() const;

    QColor screenBlockScreenBackgroundColor() const;
    bool checkBlockScreenBackgroundColor() const;

    QPixmap blockScreenBackgroundImage() const;
    bool checkBlockScreenBackgroundImage() const;

    QColor blockScreenTimeColor() const;
    bool checkBlockScreenTimeColor() const;

    int blockScreenTimeSize() const;
    bool checkBlockScreenTimeSize() const;

    QColor blockScreenMessageColor() const;
    bool checkBlockScreenMessageColor() const;

    int blockScreenMessageSize() const;
    bool checkBlockScreenMessageSize() const;

    unsigned int blockTimeout() const;
    bool checkBlockTimeout() const;

    std::string unlockScreenPromptBackground() const;
    bool checkUnlockScreenPromptBackground() const;

    QColor unlockScreenPromptBackgroundColor() const;
    bool checkUnlockScreenPromptBackgroundColor() const;

    QPixmap unlockScreenPromptBackgroundImage() const;
    bool checkUnlockScreenPromptBackgroundImage() const;

    std::string unlockScreenPromptLogo() const;
    bool checkUnlockScreenPromptLogo() const;

    bool unlockScreenPromptLogoShow() const;
    bool checkUnlockScreenPromptLogoShow() const;

    QColor unlockScreenPromptMessageColor() const;
    bool checkUnlockScreenPromptMessageColor() const;

    int unlockScreenPromptMessageSize() const;
    bool checkUnlockScreenPromptMessageSize() const;

    unsigned int unlockScreenPromptTimeout() const;
    bool checkUnlockScreenPromptTimeout() const;

    unsigned int unlockAttempts() const;
    bool checkUnlockAttempts() const;

    std::string lockScreenLogo() const;
    bool checkLockScreenLogo() const;

    bool lockScreenLogoShow() const;
    bool checkLockScreenLogoShow() const;

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
