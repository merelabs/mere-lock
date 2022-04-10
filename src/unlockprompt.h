#ifndef UNLOCKPROMPT_H
#define UNLOCKPROMPT_H

#include <QObject>

class UnlockPrompt : public QObject
{
    Q_OBJECT
public:
    explicit UnlockPrompt(QObject *parent = nullptr);

signals:

};

#endif // UNLOCKPROMPT_H
