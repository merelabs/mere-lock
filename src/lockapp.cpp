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
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configOption("config", "Set the path of the configuration file", "path", "mere/lock.conf");
    QCommandLineOption screenOption("screen", "Set the flag to lock the system's screens.");
    QCommandLineOption systemOption("system", "Set the flag to lock the system.");
    parser.parse(QCoreApplication::arguments());

    m_config = Mere::Lock::Config::instance(parser.value(configOption).toStdString());

    m_locker = new Mere::Lock::Locker;
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
