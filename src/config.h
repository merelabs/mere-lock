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


    bool ask() const;
    void ask(bool ask);

    std::string password() const;
    void password(const std::string &password);

    unsigned int timeout() const;
    void timeout(unsigned int timeout);

    //
    // Prompt
    //
    std::string promptBackground() const;
    bool checkPromptBackground() const;

    QColor promptBackgroundColor() const;
    bool checkPromptBackgroundColor() const;

    QPixmap promptBackgroundImage() const;
    bool checkPromptBackgroundImage() const;

    QPixmap promptLogo() const;
    bool checkPromptLogo() const;

    bool promptLogoShow() const;
    bool checkPromptLogoShow() const;

    QColor promptMessageColor() const;
    bool checkPromptMessageColor() const;

    int promptMessageSize() const;
    bool checkPromptMessageSize() const;

    unsigned int promptTimeout() const;
    bool checkPromptTimeout() const;

    QColor promptTimebarColor() const;
    bool checkPromptTimebarColor() const;

    //
    // lock
    //
    std::string lockScreenBackground() const;
    bool checkLockScreenBackground() const;

    QColor lockScreenBackgroundColor() const;
    bool checkLockScreenBackgroundColor() const;

    QPixmap lockScreenBackgroundImage() const;
    bool checkLockScreenBackgroundImage() const;

    QColor lockScreenTimeFontColor() const;
    bool checkLockScreenTimeFontColor() const;

    int lockScreenTimeFontSize() const;
    bool checkLockScreenTimeFontSize() const;

    QColor lockScreenMessageFontColor() const;
    bool checkLockScreenMessageFontColor() const;

    int lockScreenMessageFontSize() const;
    bool checkLockScreenMessageFontSize() const;

    //
    // lock screen prompt
    //
    std::string lockScreenPromptBackground() const;
    bool checkLockScreenPromptBackground() const;

    QColor lockScreenPromptBackgroundColor() const;
    bool checkLockScreenPromptBackgroundColor() const;

    QPixmap lockScreenPromptBackgroundImage() const;
    bool checkLockScreenPromptBackgroundImage() const;

    QPixmap lockScreenPromptLogo() const;
    bool checkLockScreenPromptLogo() const;

    bool lockScreenPromptLogoShow() const;
    bool checkLockScreenPromptLogoShow() const;

    QColor lockScreenPromptMessageColor() const;
    bool checkLockScreenPromptMessageColor() const;

    int lockScreenPromptMessageSize() const;
    bool checkLockScreenPromptMessageSize() const;

    unsigned int lockScreenPromptTimeout() const;
    bool checkLockScreenPromptTimeout() const;

    //
    // block
    //
    std::string blockScreenBackground() const;
    bool checkBlockScreenBackground() const;

    QColor blockScreenBackgroundColor() const;
    bool checkBlockScreenBackgroundColor() const;

    QPixmap blockScreenBackgroundImage() const;
    bool checkBlockScreenBackgroundImage() const;

    QColor blockScreenTimeFontColor() const;
    bool checkBlockScreenTimeFontColor() const;

    int blockScreenTimeFontSize() const;
    bool checkBlockScreenTimeFontSize() const;

    QColor blockScreenMessageFontColor() const;
    bool checkBlockScreenMessageFontColor() const;

    int blockScreenMessageFontSize() const;
    bool checkBlockScreenMessageFontSize() const;

    unsigned int blockTimeout() const;
    bool checkBlockTimeout() const;

    //
    // unlock
    //
    std::string unlockScreenBackground() const;
    bool checkUnlockScreenBackground() const;

    QColor unlockScreenBackgroundColor() const;
    bool checkUnlockScreenBackgroundColor() const;

    QPixmap unlockScreenBackgroundImage() const;
    bool checkUnlockScreenBackgroundImage() const;


    //
    // unlock screen prompt
    //
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
