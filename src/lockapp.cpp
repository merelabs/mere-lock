#include "lockapp.h"
#include "lockscreen.h"

#include "mere/utils/apputils.h"
#include "mere/utils/i18nutils.h"

#include <iostream>
#include <QCommandLineParser>

LockApp::~LockApp()
{
    if (m_locker)
    {
        delete m_locker;
        m_locker = nullptr;
    }
}

LockApp::LockApp(int &argc, char **argv)
    : Mere::Widgets::DefaultApp(argc, argv),
      m_config(nullptr)
{
    setObjectName("LockApp");

    setAppCode(Mere::Lock::AppCode.toStdString());
    setApplicationName(Mere::Lock::AppName);
    setApplicationVersion(Mere::Lock::AppVersion);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configOption(QStringList() << "c" << "config", "Set the path of the configuration file",
                                    "path",
                                    "mere/lock.conf");

    QCommandLineOption passwordOption(QStringList() << "p" << "password", "Set the password to be used to unlock the screen",
                                    "password");

    QCommandLineOption screenOption("screen", "Set the flag to lock the system's screens only.");
    //QCommandLineOption systemOption("system", "Set the flag to lock the system.");

    QCommandLineOption strictOption("strict", "Set the flag to validate the loking configuration.");

    parser.addOptions({configOption, passwordOption, screenOption, strictOption});

    parser.process(QCoreApplication::arguments());


    m_config = Mere::Lock::Config::instance(parser.value(configOption).toStdString(),
                                            parser.isSet(strictOption)
                                                ? Mere::Config::Spec::Strict::Hard
                                                : Mere::Config::Spec::Strict::Soft);

    std::cout << "Applying following configuration - " << m_config->path() << std::endl;
    try
    {
        m_config->load();
    }
    catch (const std::exception &ex)
    {
        std::cout << "Malformed configuration, check the configuration and try again" << m_config->path() << std::endl;
        std::exit(1);
    }

    if (parser.isSet(strictOption) && m_config->validate())
    {
        std::cout << "Check the configuration and try again" << std::endl;
        std::exit(1);
    }

    if (parser.isSet(passwordOption))
    {
        m_config->password(parser.value(passwordOption).toStdString());
    }

    Mere::Utils::I18nUtils::apply();

    m_locker = new Mere::Lock::Locker(this);
    connect(m_locker, &Mere::Lock::Locker::unlocked, [&](){
        quit();
    });
}

int LockApp::start()
{
    m_locker->lock();
    return 0;
}
