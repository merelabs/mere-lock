#ifndef MERE_LOCK_PROMPT_H
#define MERE_LOCK_PROMPT_H

#include <QLabel>

namespace Mere
{
namespace Lock
{

class Ticker;
class Config;
class Waitbar;
class Secret;

class Prompt : public QWidget
{
    Q_OBJECT
public:
    ~Prompt();
    explicit Prompt(QWidget *parent = nullptr);

    std::string input() const;

protected:
    void setVisible(bool visible) override;

private:
    void initUI();
    void setShadow();
    void setBackground();
    void setPromptLogo();
    void setTimeout();

    void initMessageUI();

signals:
    void attempted();
    void cancelled();

private slots:
    void clear();

private:
    QLabel *m_result;

    Mere::Lock::Secret *m_secret;
    Mere::Lock::Ticker *m_ticker;
    Mere::Lock::Waitbar *m_timeout;

    Mere::Lock::Config *m_config;
};

}
}

#endif // MERE_LOCK_PROMPT_H
