#include "lockapp.h"

#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setSetuidAllowed(true);
    LockApp app(argc, argv);
    int err = app.init();
    if (err) ::exit(err);

    err = app.start();
    if (err) ::exit(err);

    return app.exec();
}


