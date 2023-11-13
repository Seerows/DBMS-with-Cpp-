#include "DatabaseScreen.h"
#include "ui_DatabaseScreen.h"

DatabaseScreen::DatabaseScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseScreen)
{
    ui->setupUi(this);
}

DatabaseScreen::~DatabaseScreen()
{
    delete ui;
}

void DatabaseScreen::on_pushButton_clicked()
{
    QString text;
    text = ui->textEdit->toPlainText();
   // qDebug() << text;

    QStringList textLines = text.split("\n");

    //qDebug() << textLines[0];


//    for(int i=0; i<textLines.size(); i++)
//    {
//        //input.push_back(QString(textLines[i]).toStdString());
//        input.enQueue(QString(textLines[i]).toStdString());
//    }


    //input2 = g1.GetWords(input);


}

