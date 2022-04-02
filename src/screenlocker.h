#ifndef SCREELOCKER_H
#define SCREELOCKER_H

#include <QObject>

class ScreenLocker : public QObject
{
    Q_OBJECT
public:
    explicit ScreenLocker(QObject *parent = nullptr);

signals:

};

#endif // SCREELOCKER_H
