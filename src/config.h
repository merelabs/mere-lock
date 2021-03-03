#ifndef MERE_DISPLAY_CONFIG_H
#define MERE_DISPLAY_CONFIG_H

#include "mere/config/config.h"

#include <QObject>
#include <QVariant>

namespace Mere
{
namespace Lock
{

class Config : public Mere::Config::Config
{
    explicit Config(QObject *parent = nullptr);
    explicit Config(const std::string &path, QObject *parent = nullptr);

    Q_OBJECT
public:
    int init();

    QVariant get(const std::string &key) const;
    void set(const std::string &key, const QVariant &value);

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

private:
    std::map<std::string, QVariant> m_properties;
};

}
}

#endif // MERE_DISPLAY_CONFIG_H
