/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSet_username;
    QAction *actionAdd_user;
    QWidget *centralwidget;
    QListWidget *friends;
    QMenuBar *menubar;
    QMenu *menughdghgf;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(253, 373);
        actionSet_username = new QAction(MainWindow);
        actionSet_username->setObjectName(QString::fromUtf8("actionSet_username"));
        actionAdd_user = new QAction(MainWindow);
        actionAdd_user->setObjectName(QString::fromUtf8("actionAdd_user"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        friends = new QListWidget(centralwidget);
        friends->setObjectName(QString::fromUtf8("friends"));
        friends->setGeometry(QRect(10, 0, 231, 341));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 253, 22));
        menughdghgf = new QMenu(menubar);
        menughdghgf->setObjectName(QString::fromUtf8("menughdghgf"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menughdghgf->menuAction());
        menughdghgf->addSeparator();
        menughdghgf->addSeparator();
        menughdghgf->addAction(actionSet_username);
        menughdghgf->addAction(actionAdd_user);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Messenger", nullptr));
        actionSet_username->setText(QApplication::translate("MainWindow", "Set username", nullptr));
        actionAdd_user->setText(QApplication::translate("MainWindow", "Add user", nullptr));
        menughdghgf->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
