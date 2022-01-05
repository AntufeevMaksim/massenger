#ifndef SETUSERNAME_H
#define SETUSERNAME_H

#include <QMainWindow>
#include <memory>
#include "ui_setusername.h"
#include "serverinterface.h"
namespace Ui {
class SetUsername;
}

class SetUsername : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetUsername(QWidget *parent, QString *username, ServerInterface *server);

private slots:
    void on_accept_username_clicked(QAbstractButton*);

private:
    ServerInterface *_server;
    QString *_username;
    std::unique_ptr<Ui::SetUsername> ui = std::make_unique<Ui::SetUsername>();
};

#endif // SETUSERNAME_H
