#ifndef ADD_NEW_USER_H
#define ADD_NEW_USER_H

#include <QObject>
#include <QWidget>
#include <QListWidget>

class add_new_user : public QWidget
{
private:
    QListWidget *all_users = new QListWidget;

private slots:
    void onListAllUsersClicked(QListWidgetItem* item);

public:
    add_new_user(QWidget *parent, QListWidget* friends);
    ~add_new_user();
};

#endif // ADD_NEW_USER_H
