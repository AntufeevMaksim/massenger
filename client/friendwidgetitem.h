#ifndef FRIENDWIDGETITEM_H
#define FRIENDWIDGETITEM_H

#include <QListWidgetItem>

class FriendWidgetItem : public QListWidgetItem
{
public:
    void SetUserId(int id);
    int GetUserId();
protected:
    int user_id;
};

#endif // FRIENDWIDGETITEM_H
