#include "DatabaseLogin.h"
#include "ui_DatabaseLogin.h"
#include <iostream>

DatabaseLogIn::DatabaseLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseLogIn)
{
    ui->setupUi(this);


    ui->pushButton_3->setStyleSheet(
        "QPushButton:hover {background-color: rgb(173,216,230);}"
        "QPushButton {background-color: blue;}"
        );
    ui->pushButton_4->setStyleSheet(
        "QPushButton:hover {background-color: rgb(255,127,127);}"
        "QPushButton {background-color: red}"
    );

    QString inputStyling = "QLineEdit {font-weight: bold}";

    ui->lineEdit_Userid->setStyleSheet(inputStyling);
    ui->lineEdit_databasePass->setStyleSheet(inputStyling);

    ui->label_error->hide();
    ui->label_error_2->hide();

    obj = new DatabaseScreen();

    ui->lineEdit_databasePass->setEchoMode(QLineEdit::Password);
}

DatabaseLogIn::~DatabaseLogIn()
{
    delete ui;
}

void DatabaseLogIn::setText(QString text)
{
    ui->label_databaseName->setText(text);
}

bool DatabaseLogIn::verify(QString inputName, QString inputPass)
{
    std::string text = QString(ui->label_databaseName->text()).toStdString();
    int pos = text.find('\n');

    std::string text2 = text.substr(0, pos);

    databaseName = QString::fromStdString(text2);

    QFile file(databaseName + ".dat");
    QString userName;
    QString password;
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);

        in >> userName;
        in >> password;
        file.close();
    }
    else
    {
        qDebug() << "File not found";
    }

    if(inputName == userName && inputPass == password)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



void DatabaseLogIn::on_pushButton_clicked()
{
    if(ui->lineEdit_databasePass->echoMode() == QLineEdit::Password)
    {
        ui->lineEdit_databasePass->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEdit_databasePass->setEchoMode(QLineEdit::Password);

    }
}


void DatabaseLogIn::on_pushButton_3_clicked()
{

    if(!ui->lineEdit_Userid->text().isEmpty() && !ui->lineEdit_databasePass->text().isEmpty())
    {
        if(verify(ui->lineEdit_Userid->text(), ui->lineEdit_databasePass->text()))
        {
            setVisible(false);
            ui->label_error->hide();
            ui->label_error_2->hide();
            obj->setName(databaseName);
            close();
            obj->display();
            obj->showMaximized();
            obj->show();
            bool value = 1;
            emit closeSignal(value);
            qDebug() << "Access Granted";

        }
        else
        {
            ui->label_error_2->hide();
            ui->label_error->show();
        }
    }
    else
    {
        ui->label_error_2->show();
        ui->label_error->hide();
    }

}


void DatabaseLogIn::on_pushButton_4_clicked()
{
    close();
}

