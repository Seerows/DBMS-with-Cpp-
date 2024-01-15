#include "MainScreen.h"
#include "ui_MainScreen.h"
#include <iostream>
#include <QMessageBox>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignHCenter);

    backgroundPixmap = new QPixmap;

    layoutDatabaseName = new QGridLayout(ui->frame);
    layoutDatabaseName->setVerticalSpacing(10);
    layoutDatabaseName->setHorizontalSpacing(50);
    layoutDatabaseName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    x=0;
    y=0;
    count = 0;
    QFile file("userData.txt");

    if(file.open(QIODevice::Append)){
        file.close();
    }

    displayDatabaseName();

    ui->label->setStyleSheet(
        "QLabel:hover {color:teal;}"
        "QLabel { color: black; text-decoration: underline; font: 900 50pt Segoe UI Black; background-color: transparent;}"
        );

    ui->btn_createDatabase->setStyleSheet(
        "QPushButton:hover {background-color: green; color: white;}"
        "QPushButton {background-color : white; color: blue; font-weight: bold; font-size: 25; border: 2px solid black; border-radius: 10px;}"
        );

    obj = new CreateDatabase;
    obj2 = new DatabaseLogIn;

}

void MainScreen:: paintEvent(QPaintEvent *event)
{
    backgroundPixmap->load(":/images/MainScreen.jpeg");
    QPainter painter(this);
    painter.drawPixmap(0, 0, *backgroundPixmap);

    *backgroundPixmap = backgroundPixmap->scaled(size(), Qt::KeepAspectRatio);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    setAutoFillBackground(true);
}

MainScreen::~MainScreen()
{
    delete obj;
    delete obj2;
    delete ui;
}

void MainScreen::displayDatabaseName()
{
    QFile file("userData.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QStringList data1;
    QStringList data2;

    int i=0;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(i%2==0)
        {
            data1.append(line);
        }
        else
        {
            data2.append(line);
        }
        i++;
    }

    file.close();

    if(i == 0){
        return;
    }

    databaseName = new QPushButton[data1.count()];
    databaseName->setParent(ui->frame);

    for(int i=count; i<data1.count(); i++)
    {
        if(x % 5 == 4)
        {
            y=0;
        }

        databaseName[i].setFixedWidth(200);
        databaseName[i].setFixedHeight(200);
        layoutDatabaseName->addWidget(&databaseName[i], x/4, y++);
        x++;
        count++;
    }

    for(int i=0; i<data1.count(); i++)
    {
        databaseName[i].setText(data1[i].toUpper() + "\n" + data2[i]);
        databaseName[i].setStyleSheet(
            "QPushButton:hover {background-color: purple; color: white;}"
            "QPushButton {background-color : #ADD8E6; font-weight: bold; font-size: 25; border: 2px solid black; border-radius: 10px;}"

            );

    }

    for(int i=0; i<data1.count(); i++)
    {
        int count = 0;
        connect(&databaseName[i], &QPushButton::clicked, [i, &count, this](){
            count = i;
            onClick(databaseName[i].text());
        });

    }

}

void MainScreen::onClick(QString text)
{
    obj2->setText(text);
    connect(obj2, &DatabaseLogIn::closeSignal, this, &MainScreen::handleLoginSuccess);
    obj2->exec();
}


void MainScreen::on_btn_createDatabase_clicked()
{

    obj->setWindowTitle("Create Database");
    connect(obj, &CreateDatabase::enteredDatabaseName, this, &MainScreen::displayDatabaseName);
    obj->show();
}

void MainScreen::handleLoginSuccess(bool value)
{

    if(value == 1)
    {
        close();
    }

}


