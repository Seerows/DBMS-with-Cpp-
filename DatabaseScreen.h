#ifndef DATABASESCREEN_H
#define DATABASESCREEN_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <tuple>
#include <QRegularExpression>
#include <QDebug>
#include "getWords.h"
#include "Queue.h"
#include "validateQuery.h"
#include "Database.h"

using namespace std;

namespace Ui {
class DatabaseScreen;
}

class DatabaseScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatabaseScreen(QWidget *parent = nullptr);
    ~DatabaseScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DatabaseScreen *ui;
    Database db;
    getWords g1;

};

#endif // DATABASESCREEN_H
