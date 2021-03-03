#include "lockapp.h"
#include "lockscreen.h"

#include <QFile>
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
    : QApplication(argc, argv)
{
    setObjectName("MereLockApp");
//    setProperty("AppCode", APP_CODE);
//    setApplicationName(APP_NAME);
//    setApplicationVersion(APP_VERSION);


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

    // Apply Styles
    QFile File(":/lock/lock.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    setStyleSheet(StyleSheet);
}

int LockApp::init()
{
    return 0;
}

int LockApp::start()
{
    m_locker->lock();
    return 0;
}
