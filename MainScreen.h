#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include "CreateDatabase.h"
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include "DatabaseLogin.h"
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScreen; }
QT_END_NAMESPACE

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    void onClick(QString text);
    ~MainScreen();

private slots:
    void on_btn_createDatabase_clicked();
    void handleLoginSuccess(bool value);

private:
    Ui::MainScreen *ui;
    QPixmap *backgroundPixmap;
    QWidget *mainWidget;
    QGridLayout *layoutDatabaseName;
    QPushButton *databaseName;
    void displayDatabaseName();
    void paintEvent(QPaintEvent *event);
    int x, y;
    int count;
    CreateDatabase *obj;
    DatabaseLogIn *obj2;
};
#endif // MAINSCREEN_H
