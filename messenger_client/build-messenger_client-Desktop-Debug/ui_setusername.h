/********************************************************************************
** Form generated from reading UI file 'setusername.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUSERNAME_H
#define UI_SETUSERNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUsername
{
public:
    QWidget *centralwidget;
    QLineEdit *username_edit;
    QDialogButtonBox *accept_username;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SetUsername)
    {
        if (SetUsername->objectName().isEmpty())
            SetUsername->setObjectName(QString::fromUtf8("SetUsername"));
        SetUsername->resize(255, 91);
        centralwidget = new QWidget(SetUsername);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        username_edit = new QLineEdit(centralwidget);
        username_edit->setObjectName(QString::fromUtf8("username_edit"));
        username_edit->setGeometry(QRect(10, 10, 241, 25));
        accept_username = new QDialogButtonBox(centralwidget);
        accept_username->setObjectName(QString::fromUtf8("accept_username"));
        accept_username->setGeometry(QRect(80, 40, 166, 25));
        accept_username->setCursor(QCursor(Qt::ArrowCursor));
        accept_username->setStandardButtons(QDialogButtonBox::Ok);
        accept_username->setCenterButtons(false);
        SetUsername->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SetUsername);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SetUsername->setStatusBar(statusbar);

        retranslateUi(SetUsername);

        QMetaObject::connectSlotsByName(SetUsername);
    } // setupUi

    void retranslateUi(QMainWindow *SetUsername)
    {
        SetUsername->setWindowTitle(QApplication::translate("SetUsername", "Set username", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetUsername: public Ui_SetUsername {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUSERNAME_H
