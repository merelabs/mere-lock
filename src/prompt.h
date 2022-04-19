#ifndef MERE_LOCK_PROMPT_H
#define MERE_LOCK_PROMPT_H

#include <QLabel>

namespace Mere
{
namespace Lock
{

class Ticker;
class Config;
class Timebar;
class Secret;

class Prompt : public QWidget
{
    Q_OBJECT
public:
    ~Prompt();
    explicit Prompt(QWidget *parent = nullptr);

    std::string input() const;
    void prompt(const std::string &prompt);
    void message(const std::string &message);
    void prompt(){showNormal();}


protected:
    virtual void initUI();
    virtual void setBackground();
    virtual void setPromptLogo();

    void setVisible(bool visible) override;
    void setLogo(QPixmap pixmap);

private:
    void setShadow();
    void setTimeout();

    void initMessageUI();

signals:
    void entered();
    void escaped();

private slots:
    void clear();

private:
    QLabel *m_logo;
    QLabel *m_prompt;
    QLabel *m_message;

    Mere::Lock::Secret *m_secret;
    Mere::Lock::Ticker *m_ticker;
    Mere::Lock::Timebar *m_timeout;

    Mere::Lock::Config *m_config;
};

}
}

#endif // MERE_LOCK_PROMPT_H
