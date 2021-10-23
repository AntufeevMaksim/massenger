#include "setusername.h"
#include "ui_setusername.h"
#include "userdata.h"
SetUsername::SetUsername(QWidget *parent, QString *username, ServerInterface *server):
    QMainWindow(parent)
{
    _server = server;
    _username = username;
    ui->setupUi(this);
}

void SetUsername::on_accept_username_clicked(QAbstractButton*)
{
    *_username = ui->username_edit->text();
    _server->SendUsername(*(_username));
    UserData::SetUsername(*_username);
    ui->username_edit->clear();
}
