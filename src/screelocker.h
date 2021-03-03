#ifndef SCREELOCKER_H
#define SCREELOCKER_H

#include <QObject>

class ScreeLocker : public QObject
{
    Q_OBJECT
public:
    explicit ScreeLocker(QObject *parent = nullptr);

signals:

};

#endif // SCREELOCKER_H
