#ifndef MERE_LOCK_SECRET_H
#define MERE_LOCK_SECRET_H

#include <QDebug>
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
    explicit Secret(QWidget *parent = nullptr);

    std::string secret() const;

protected:
//    void setVisible(bool visible) override;
    void keyPressEvent(QKeyEvent *keyEvent) override;

signals:
    void changed();
    void entered();
    void escaped();
};

}
}
#endif // MERE_LOCK_SECRET_H
