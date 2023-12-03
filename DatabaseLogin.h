#ifndef DATABASELOGIN_H
#define DATABASELOGIN_H
#include <QFile>
#include <QDialog>
#include <QMessageBox>
#include "DatabaseScreen.h"

namespace Ui {
class DatabaseLogIn;
}

class DatabaseLogIn : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseLogIn(QWidget *parent = nullptr);
    ~DatabaseLogIn();
    void setText(QString text);
    bool verify(QString inputName, QString inputPass);

signals:
    void closeSignal(bool value);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DatabaseLogIn *ui;
    DatabaseScreen *obj;
    QString databaseName;

};

#endif // DATABASELOGIN_H
