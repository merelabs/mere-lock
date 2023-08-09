#ifndef MERE_LOCK_SECRET_H
#define MERE_LOCK_SECRET_H

#include <QKeyEvent>
#include <QLineEdit>

namespace Mere
{
namespace Lock
{

class Secret : public QLineEdit
{
    Q_OBJECT
public:
    virtual ~Secret();
    explicit Secret(QWidget *parent = nullptr);

    std::string secret() const;

protected:
    void keyPressEvent(QKeyEvent *keyEvent) override;

signals:
    void changed();
    void entered();
    void escaped();
};

}
}
#endif // MERE_LOCK_SECRET_H
