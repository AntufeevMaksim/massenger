/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QWidget *centralwidget;
    QPushButton *send_message_button;
    QTextEdit *user_message;
    QListWidget *user_chat;
    QLineEdit *friend_name;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName(QString::fromUtf8("Chat"));
        Chat->resize(390, 626);
        centralwidget = new QWidget(Chat);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        send_message_button = new QPushButton(centralwidget);
        send_message_button->setObjectName(QString::fromUtf8("send_message_button"));
        send_message_button->setGeometry(QRect(290, 570, 89, 25));
        user_message = new QTextEdit(centralwidget);
        user_message->setObjectName(QString::fromUtf8("user_message"));
        user_message->setGeometry(QRect(10, 440, 371, 121));
        user_chat = new QListWidget(centralwidget);
        user_chat->setObjectName(QString::fromUtf8("user_chat"));
        user_chat->setGeometry(QRect(10, 50, 371, 381));
        user_chat->setFocusPolicy(Qt::StrongFocus);
        friend_name = new QLineEdit(centralwidget);
        friend_name->setObjectName(QString::fromUtf8("friend_name"));
        friend_name->setGeometry(QRect(10, 10, 371, 25));
        friend_name->setEchoMode(QLineEdit::Normal);
        friend_name->setAlignment(Qt::AlignCenter);
        friend_name->setReadOnly(true);
        Chat->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Chat);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Chat->setStatusBar(statusbar);

        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QMainWindow *Chat)
    {
        Chat->setWindowTitle(QApplication::translate("Chat", " Chat", nullptr));
        send_message_button->setText(QApplication::translate("Chat", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
