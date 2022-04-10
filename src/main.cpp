#include "lockapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setSetuidAllowed(true);
    LockApp app(argc, argv);
    int err = app.init();
    if (err) std::exit(err);

    err = app.start();
    if (err) std::exit(err);

    return app.exec();
}
