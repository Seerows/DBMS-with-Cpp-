#include "CreateDatabase.h"
#include "ui_CreateDatabase.h"
#include "ui_MainScreen.h"

CreateDatabase::CreateDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDatabase)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setStyleSheet(
        "QPushButton:hover {background-color: rgb(173,216,230); color: white}"
        "QPushButton {background-color: blue; color: white}"
    );
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setStyleSheet(
        "QPushButton:hover {background-color: rgb(255,127,127); color: white}"
        "QPushButton {background-color: red; color: white}"
    );

    QString inputStyling = "QLineEdit {color: white; font-size:14px; font-weight: bold}";
    ui->input_databaseName->setStyleSheet(inputStyling);
    ui->input_userName->setStyleSheet(inputStyling);
    ui->input_userPassword->setStyleSheet(inputStyling);
    ui->input_userPassword_2->setStyleSheet(inputStyling);
    ui->label_error1->hide();
    ui->label_error2->hide();
    ui->label_error3->hide();

    QString errorStyleSheet = "QLabel{color: white}";

    ui->label_error1->setStyleSheet(errorStyleSheet);
    ui->label_error2->setStyleSheet(errorStyleSheet);
    ui->label_error3->setStyleSheet(errorStyleSheet);

    ui->input_userPassword->setEchoMode(QLineEdit::Password);
    ui->input_userPassword_2->setEchoMode(QLineEdit::Password);

    QString string = "color: white";
    ui->pushButton->setStyleSheet(string);
    ui->pushButton_2->setStyleSheet(string);

}


CreateDatabase::~CreateDatabase()
{
    qDebug() << "Destructor";
    delete ui;
}

bool verify(QString name)
{
    QFile file("userData.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QStringList data1;
    int i=0;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(i%2==0)
        {
            data1.append(line);
        }
        i++;
    }
    file.close();

    for(int i=0; i<data1.size(); i++)
    {
        if(data1[i] == name)
        {
            return 1;
        }
    }

    return 0;
}



void CreateDatabase::on_buttonBox_accepted()
{
    if(!ui->input_databaseName->text().isEmpty() && !ui->input_databaseName->text().contains(' ') && !ui->input_userName->text().isEmpty() && !ui->input_userPassword->text().isEmpty())
    {
        if(verify(ui->input_databaseName->text()) == 0)
        {
            if(ui->input_userPassword->text() == ui->input_userPassword_2->text())
            {
                setVisible(false);
                emit enteredDatabaseName(ui->input_databaseName->text().toLower(), ui->input_userName->text().toLower());
                Database obj(QString(ui->input_databaseName->text().toLower()).toStdString(), QString(ui->input_userName->text().toLower()).toStdString(), QString(ui->input_userPassword->text()).toStdString());
                obj.username = QString(ui->input_userName->text().toLower()).toStdString();
                obj.password = QString(ui->input_userPassword->text()).toStdString();
                qDebug() << obj.username;
                qDebug() << obj.password;
                obj.commit();
                //close();
            }
            else
            {
                ui->label_error1->hide();
                ui->label_error2->hide();
                ui->label_error3->show();
            }
        }
        else
        {
            ui->label_error1->hide();
            ui->label_error2->show();
            ui->label_error3->hide();
        }
    }
    else
    {
        qDebug() << "IN else block";
        ui->label_error1->show();
        ui->label_error2->hide();
        ui->label_error3->hide();
    }
    setVisible(true);
}

void CreateDatabase::on_pushButton_clicked()
{
    if(ui->input_userPassword->echoMode() == QLineEdit::Password)
    {
        ui->input_userPassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->input_userPassword->setEchoMode(QLineEdit::Password);
    }
}


void CreateDatabase::on_pushButton_2_clicked()
{
    if(ui->input_userPassword_2->echoMode() == QLineEdit::Password)
    {
        ui->input_userPassword_2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->input_userPassword_2->setEchoMode(QLineEdit::Password);
    }
}

