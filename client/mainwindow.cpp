#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QObject>


void MainWindow::onListMailItemClicked(QListWidgetItem* item)
{
    QString name = item->text();
    printf("%s\n", name.toStdString().c_str());
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//QListWidgetItem *newItem = new QListWidgetItem;
//newItem->setText("newitem");
//connect(ui->Friends, SIGNAL(itemClicked(QListWidgetItem*)),
//            this, SLOT(onListMailItemClicked(QListWidgetItem*)));
//
//ui->Friends->insertItem(1, newItem);


void MainWindow::on_actionAdd_user_triggered()
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText("newitem");
    connect(ui->Friends, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListMailItemClicked(QListWidgetItem*)));

    ui->Friends->insertItem(1, newItem);
}
