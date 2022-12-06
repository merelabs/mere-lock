#ifndef MERE_LOCK_CONFIG_H
#define MERE_LOCK_CONFIG_H

#include "mere/config/kvconfig.h"

#include <QFont>
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

    //
    // lock
    //
    QVariant lockScreenBackground() const;
    bool checkLockScreenBackground() const;

    QFont lockScreenStopwatchFont() const;
    bool checkLockScreenStopwatchFont() const;

    QColor lockScreenStopwatchColor() const;
    bool checkLockScreenStopwatchColor() const;

    QColor lockScreenMessageColor() const;
    bool checkLockScreenMessageColor() const;

    QFont lockScreenMessageFont() const;
    bool checkLockScreenMessageFont() const;

    //
    // block
    //
    QVariant blockScreenBackground() const;
    bool checkBlockScreenBackground() const;

    QColor blockScreenStopwatchColor() const;
    bool checkBlockScreenStopwatchColor() const;

    QFont blockScreenStopwatchFont() const;
    bool checkBlockScreenStopwatchFont() const;

    QColor blockScreenMessageColor() const;
    bool checkBlockScreenMessageColor() const;

    QFont blockScreenMessageFont() const;
    bool checkBlockScreenMessageFont() const;

    unsigned int blockTimeout() const;
    bool checkBlockTimeout() const;

    //
    // unlock
    //
    QVariant unlockPromptBackground() const;
    bool checkUnlockPromptBackground() const;

    std::string unlockPromptLogo() const;
    bool checkUnlockPromptLogo() const;

    bool unlockPromptLogoShow() const;
    bool checkUnlockPromptLogoShow() const;

    QColor unlockPromptMessageColor() const;
    bool checkUnlockPromptMessageColor() const;

    QFont unlockPromptMessageFont() const;
    bool checkUnlockPromptMessageFont() const;

    unsigned int unlockPromptTimeout() const;
    bool checkUnlockPromptTimeout() const;

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
    bool checkKey(const std::string &key, std::string &value) const;

    bool checkColor(const std::string &key) const;
    bool checkImage(const std::string &key) const;
    bool checkFont(const std::string &key) const;

    QFont font(const std::string &key, const QFont &font) const;
    QColor color(const std::string &key, const QColor &color) const;
    QVariant background(const std::string &key, const QVariant &background) const;

    bool value(const std::string &key, const bool &default_value) const;
    std::string value(const std::string &key, const std::string &default_value) const;
};

}
}

#endif // MERE_LOCK_CONFIG_H
