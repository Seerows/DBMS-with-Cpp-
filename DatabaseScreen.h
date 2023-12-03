#ifndef DATABASESCREEN_H
#define DATABASESCREEN_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "Table.h"
#include "Database.h"
#include "getWords.h"
#include <QPushButton>
#include <QGridLayout>
#include "displaytable.h"
#include <QHBoxLayout>

namespace Ui {
class DatabaseScreen;
}

class DatabaseScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatabaseScreen(QWidget *parent = nullptr);
    QString databaseName;
    void display();
    void setName(QString name);
    ~DatabaseScreen();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::DatabaseScreen *ui;

    void createTable(Table *obj);
    QPushButton *tableButton;
    int count;
    void displayTable(Table *obj);
    QGridLayout *layout;
    int x, y;
    DisplayTable *table;
    void addTable(Table *obj);
    Database db;
    getWords g1;
};

#endif // DATABASESCREEN_H
