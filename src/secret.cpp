#include "secret.h"

Mere::Lock::Secret::Secret(QWidget *parent)
    : QLineEdit(parent)
{
    setAlignment(Qt::AlignCenter);
    setEchoMode(QLineEdit::Password);
    setFocus();

    connect(this, &QLineEdit::cursorPositionChanged, this, [&](){
        emit changed();
    });

    connect(this, &QLineEdit::returnPressed, this, [&](){
        emit entered();
    });
}

std::string Mere::Lock::Secret::secret() const
{
    return text().toStdString();
}

//void Mere::Lock::Secret::setVisible(bool visible)
//{
//    if (visible)
//    {
//        clear();
//        grabKeyboard();
//    }
//    else
//    {
//        releaseKeyboard();
//    }

//    QWidget::setVisible(visible);
//}

void Mere::Lock::Secret::keyPressEvent(QKeyEvent* keyEvent)
{

    if (keyEvent->key() == Qt::Key_Escape)
    {
        qDebug() << "ESCAPED";
        emit escaped();
        return;
    }

    QLineEdit::keyPressEvent(keyEvent);
}
