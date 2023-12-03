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

    layoutDatabaseName = new QGridLayout(ui->frame);
    layoutDatabaseName->setVerticalSpacing(10);
    layoutDatabaseName->setHorizontalSpacing(50);
    layoutDatabaseName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    //scroll = new QScrollArea(this);
    //ui->frame->setFixedSize(300, 300);

    //scroll->setWidget(ui->frame);
    //scroll->show();
    //scroll->setWidgetResizable(true);
    //scroll->setBaseSize(ui->frame->width(), ui->frame->height());

    //setCentralWidget(ui->frame);

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
//        "QPushButton:hover {color: brown;}"
//        "QPushButton { font: 900 9pt Segoe UI Black; background: silver; color: white border: 2px solid black;}"
        "QPushButton:hover {background-color: green; color: white;}"
        "QPushButton {background-color : white; color: blue; font-weight: bold; font-size: 25; border: 2px solid black; border-radius: 10px;}"
        );

    obj = new CreateDatabase;
    obj2 = new DatabaseLogIn;

}

void MainScreen:: paintEvent(QPaintEvent *event)
{
    backgroundPixmap.load("E:/Seerow/FAST/Sem3/DS Project/DS Project v8/DS_Project_v8/download.jpeg");
    QPainter painter(this);
    painter.drawPixmap(0, 0, backgroundPixmap);

    backgroundPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    setAutoFillBackground(true);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::writeDatabaseName(const QString& databaseName, const QString& userName)
{
    QFile file("userData.txt");

    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << databaseName << "\n";
        out << userName << "\n";
        file.close();
        displayDatabaseName();
    }
    else
    {
        qDebug() << "Failed to append to the file.";
    }
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

    int nextline = 0;

    //    for(const QString &item : data1)
    //    {
    //        qDebug() << item;
    //    }

    //    for(const QString &item : data2)
    //    {
    //        qDebug() << item;
    //    }

    for(int i=count; i<data1.count(); i++)
    {
        if(nextline > 3)
        {
            nextline = 0;
            x++;
            y=0;
        }
        databaseName[i].setText(data1[i].toUpper() + "\n" + data2[i]);
        databaseName[i].setFixedWidth(200);
        databaseName[i].setFixedHeight(200);
        layoutDatabaseName->addWidget(&databaseName[i], x, y++);
        nextline++;
        count++;
    }

    //scroll->setWidget(ui->frame);


    for(int i=0; i<data1.count(); i++)
    {

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
    connect(obj, &CreateDatabase::enteredDatabaseName, this, &MainScreen::writeDatabaseName);
    obj->show();
}

void MainScreen::handleLoginSuccess(bool value)
{

    if(value == 1)
    {
        close();
    }

}


