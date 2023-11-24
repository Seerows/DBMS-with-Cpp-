#include "mainwindow.h"
#include <QApplication>
#include "DatabaseScreen.h"

#include <iostream>
#include "Table.h"
#include "Database.h"
#include "getwords.h"
#include "validatequery.h"
#include "Column.h"

using namespace std;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    DatabaseScreen ds;
    ds.show();

    return a.exec();

}
