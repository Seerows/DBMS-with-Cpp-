#ifndef DATABASESCREEN_H
#define DATABASESCREEN_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "getWords.h"
#include "Queue.h"
#include "validateQuery.h"
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

    std::vector<std::string> input2;
    getWords g1;

};

#endif // DATABASESCREEN_H
