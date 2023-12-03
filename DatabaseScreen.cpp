#include "DatabaseScreen.h"
#include "MainScreen.h"
#include "qlabel.h"
#include "ui_DatabaseScreen.h"

DatabaseScreen::DatabaseScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseScreen)
{
    ui->setupUi(this);
    count = 0;

    layout = new QGridLayout(ui->frame);
    layout->setAlignment(Qt::AlignTop);

    x = 0;
    y = 0;

    ui->pushButton_exit->setStyleSheet(
        "QPushButton {background-color: red; color: black; font-weight: bold}"
        "QPushButton:hover {background-color: #f4c2c2; color: white; font-weight: bold}"
    );

    ui->pushButton->setStyleSheet(
        "QPushButton {background-color: blue; color: black; font-weight: bold}"
        "QPushButton:hover {background-color: #00c3e32; color: white; font-weight: bold}"
        );
}


void DatabaseScreen::setName(QString name)
{
    databaseName = name;
    ui->label_databaseName->setText(name);
    db.name = name.toStdString();
    db.pull();
}

DatabaseScreen::~DatabaseScreen()
{
    delete ui;
}

void DatabaseScreen::display()
{
    Database d1(databaseName.toStdString());

    d1.pull();

    auto *temp = d1.table_list.head;
    int i=0;

    if(temp == NULL)
    {
        return;
    }

    QStringList tableName;

    while(temp != NULL)
    {
        tableName.append(QString::fromStdString(temp->data->label));
        i++;
//        qDebug() << temp->data->label;
//        temp->data->display();
//        qDebug() << "Cols" <<temp->data->num_of_cols;
//        qDebug() << "Rows" << temp->data->num_of_rows;
        temp = temp->next;
    }

    tableButton = new QPushButton[tableName.count()];

    for(int i=count; i<tableName.count(); i++)
    {
        layout->setVerticalSpacing(10);
        tableButton[i].setParent(ui->frame);
        tableButton[i].setText(tableName[i]);
        layout->addWidget(&tableButton[i], x++, y);
        count++;
    }

    temp = d1.table_list.head;
    i=0;

    for(int i=0; i<tableName.count(); i++)
    {
        temp->data->display();
        connect(&tableButton[i], &QPushButton::clicked, [temp, this](){
            displayTable(temp->data);
        });

        temp = temp->next;
    }

}

void DatabaseScreen::displayTable(Table *obj)
{
    table = new DisplayTable();
    table->addTableObject(obj);
    table->show();
}



void DatabaseScreen::on_pushButton_clicked()
{
    QString text;
    text = ui->textEdit->toPlainText();

    QRegularExpression regex("(?<=;)");

    QStringList queries = text.split(regex);
    queries.removeAll("");

    Table* select;

    for(int i = 0; i<queries.size(); i++){
        QStringList textLines = queries.at(i).split("\n");

        Queue<std::string> input;

        for(int i=0; i<textLines.size(); i++){
            input.enQueue(QString(textLines[i]).toStdString());
        }

        vector<string> words = g1.GetWords(input);
        select = db.processQuery(words);
    }

    if(select != NULL){
        qDebug() << "Creating with " << select->num_of_cols << " cols";
        createTable(select);
        delete select;
        qDebug() << "Created";
    }

    display();

}

void DatabaseScreen::createTable(Table *obj)
{
    ui->tableWidget->setColumnCount(obj->num_of_cols);
    ui->tableWidget->setRowCount(obj->num_of_rows);

    qDebug() << ui->tableWidget->columnCount();


    for(int i=0; i<obj->num_of_cols; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString::fromStdString((*obj)[i].label));
        ui->tableWidget->setHorizontalHeaderItem(i, item);
    }

    for(int i=0; i<obj->num_of_rows; i++)
    {
        for(int j=0; j<obj->num_of_cols; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(QString::fromStdString((*obj)[j][i].getValue()));
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void DatabaseScreen::on_pushButton_exit_clicked()
{
    close();
    MainScreen *obj = new MainScreen;
    obj->show();
}

