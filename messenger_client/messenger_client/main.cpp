#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QIcon icon("./pig.ico");
//    a.setWindowIcon(icon);
//    QMainWindow::setWindowIcon("pig.ico")
    a.setWindowIcon(QIcon("свинья.ico"));
    return a.exec();
}
