#include "mainwindow.h"

#include <QApplication>
#include "DatabaseScreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DatabaseScreen o;
    o.show();



    //w.show();
    return a.exec();
}
