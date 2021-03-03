#ifndef SYSTEMLOCKER_H
#define SYSTEMLOCKER_H

#include <QObject>

class SystemLocker : public QObject
{
    Q_OBJECT
public:
    explicit SystemLocker(QObject *parent = nullptr);

signals:

};

#endif // SYSTEMLOCKER_H
