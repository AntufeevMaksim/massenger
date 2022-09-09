/********************************************************************************
** Form generated from reading UI file 'addnewfriend.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWFRIEND_H
#define UI_ADDNEWFRIEND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNewFriend
{
public:
    QWidget *centralwidget;
    QListWidget *list_all_users;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AddNewFriend)
    {
        if (AddNewFriend->objectName().isEmpty())
            AddNewFriend->setObjectName(QString::fromUtf8("AddNewFriend"));
        AddNewFriend->resize(270, 600);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("/home/maksim/Downloads/Ikons/Ikons/favicon.ico")));
        AddNewFriend->setWindowIcon(icon);
        centralwidget = new QWidget(AddNewFriend);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        list_all_users = new QListWidget(centralwidget);
        list_all_users->setObjectName(QString::fromUtf8("list_all_users"));
        list_all_users->setGeometry(QRect(0, 0, 261, 581));
        AddNewFriend->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AddNewFriend);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AddNewFriend->setStatusBar(statusbar);

        retranslateUi(AddNewFriend);

        QMetaObject::connectSlotsByName(AddNewFriend);
    } // setupUi

    void retranslateUi(QMainWindow *AddNewFriend)
    {
        AddNewFriend->setWindowTitle(QApplication::translate("AddNewFriend", "Add New Friend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddNewFriend: public Ui_AddNewFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWFRIEND_H
