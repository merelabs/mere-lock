#ifndef LOCKPROMPT_H
#define LOCKPROMPT_H

#include <QObject>

class LockPrompt : public QObject
{
    Q_OBJECT
public:
    explicit LockPrompt(QObject *parent = nullptr);

signals:

};

#endif // LOCKPROMPT_H
