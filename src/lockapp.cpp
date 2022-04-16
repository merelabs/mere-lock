#include "lockapp.h"
#include "lockscreen.h"

#include "mere/utils/apputils.h"
#include "mere/utils/i18nutils.h"
#include "mere/utils/stringutils.h"

#include <iostream>
#include <QTimer>
#include <QInputDialog>
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

    setAppCode(Mere::Lock::AppCode);
    setAppName(Mere::Lock::AppName);
    setAppVersion(Mere::Lock::AppVersion);

    Mere::Utils::I18nUtils::apply();

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("LockApp", "LockAppDescription"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configOption(QStringList() << "c" << "config", QCoreApplication::translate("LockArg", "LockArgConfig"),
                                    "path",
                                    "mere/lock.conf");

    QCommandLineOption passwordOption(QStringList() << "p" << "password", QCoreApplication::translate("LockArg", "LockArgPassword"),
                                    "password");

    QCommandLineOption timeoutOption(QStringList() << "t" << "timeout", QCoreApplication::translate("LockArg", "LockArgTimeout"),
                                    "timeout");

    QCommandLineOption screenOption("screen", QCoreApplication::translate("LockArg", "LockArgScreen"));
    //QCommandLineOption systemOption("system", "Set the flag to lock the system.");

    QCommandLineOption strictOption("strict", QCoreApplication::translate("LockArg", "LockArgStrict"));

    parser.addOptions({configOption, passwordOption, timeoutOption, screenOption, strictOption});

    //parser.process(QCoreApplication::arguments());
    bool askPassword = false;
    if(!parser.parse(QCoreApplication::arguments()))
    {
        // kind of hack to make -p/--password value optional
        QString message = parser.errorText();
        if (message.startsWith("Missing value after '-p'") || message.startsWith("Missing value after '--password'"))
        {
            askPassword = true;
//            QMessageBox msgBox;
//            msgBox.setText("The document has been modified.");
//            msgBox.exec();
//            bool ok;
//            QString text = QInputDialog::getText(0, "Input dialog",
//                                                     "Date of Birth:", QLineEdit::Normal,
//                                                     "", &ok);
            // to fake isSet
//            passwordOption.setValueName("");
        }
        else
        {
            qDebug() << message;
            std::exit(1);
        }

    }


    m_config = Mere::Lock::Config::instance(parser.value(configOption).toStdString(),
                                            parser.isSet(strictOption)
                                                ? Mere::Config::Spec::Strict::Hard
                                                : Mere::Config::Spec::Strict::Soft);
    std::cout << LockApp::tr("LockConfigApply").toStdString() << "\n - " << m_config->path() << std::endl;

    try
    {
        m_config->load();
    }
    catch (const std::exception &ex)
    {
        std::cout << LockApp::tr("LockConfigLoadFailed").toStdString() << "\n - " << m_config->path() << std::endl;
        std::exit(1);
    }

    if (parser.isSet(strictOption) && m_config->validate())
    {
        std::cout << LockApp::tr("LockConfigValidCheckFailed").toStdString() << "\n - " << m_config->path() << std::endl;
        std::exit(1);
    }

    if (parser.isSet(passwordOption))
    {
//        if (askPassword)
//        {
//            bool ok;
//            QString password = QInputDialog::getText(0, "Input dialog",
//                                                     "Enter your secret:", QLineEdit::Normal,
//                                                     "", &ok);
//            m_config->password(password.toStdString());
//        }
//        else
        std::string password = parser.value(passwordOption).toStdString();

        m_config->ask(Mere::Utils::StringUtils::isBlank(password));
        m_config->password(password);
    }

    if (parser.isSet(timeoutOption))
    {
        unsigned int timeout = parser.value(timeoutOption).toInt();
        if (timeout)
        {
            m_config->timeout(timeout);
            QTimer::singleShot(timeout * 1000 * 60, this, SLOT(quit()));
        }
    }

    m_locker = new Mere::Lock::Locker(this);
    connect(m_locker, &Mere::Lock::Locker::unlocked, [&](){
        quit();
    });
}

int LockApp::start()
{
    return m_locker->lock();
}
