#include "lockapp.h"
#include "lockscreen.h"

#include "mere/utils/apputils.h"
#include "mere/utils/i18nutils.h"

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
    : Mere::Widgets::DefaultApp(argc, argv)
{
    setObjectName("LockApp");

    setAppCode(Mere::Lock::AppCode.toStdString());
    setApplicationName(Mere::Lock::AppName);
    setApplicationVersion(Mere::Lock::AppVersion);

    Mere::Utils::I18nUtils::apply();

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configOption(QStringList() << "c" << "config", "Set the path of the configuration file",
                                    "path",
                                    "mere/lock.conf");

    QCommandLineOption passwordOption(QStringList() << "p" << "password", "Set the password to be used to unlock the screen",
                                    "password");

    QCommandLineOption screenOption("screen", "Set the flag to lock the system's screens.");
    QCommandLineOption systemOption("system", "Set the flag to lock the system.");

    parser.addOptions({configOption, passwordOption, screenOption, systemOption});

    parser.process(QCoreApplication::arguments());

    m_config = Mere::Lock::Config::instance(parser.value(configOption).toStdString());

    if (parser.isSet(passwordOption))
    {
        m_config->password(parser.value(passwordOption).toStdString());
    }

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
