#include "DatabaseScreen.h"
#include "MainScreen.h"
#include "qlabel.h"
#include "ui_DatabaseScreen.h"
#include <QImage>

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

    QString inputStyling = "QTextEdit {font-weight: bold; color: white; background-color: rgba(0, 0, 0, 0)}";

    ui->textEdit->setStyleSheet(inputStyling);

    tableButton = NULL;

    ui->label_errorMsg0->setText("Invalid Query.");
    ui->label_errorMsg1->setText("Table already exists.");
    ui->label_errorMsg2->setText("The reference table does not exist.");
    ui->label_errorMsg3->setText("The reference column does not exist.");
    ui->label_errorMsg4->setText("Invalid Insertion Input.");
    ui->label_errorMsg5->setText("Invalid Selection Input.");
    ui->label_errorMsg6->setText("Invalid Order Query.");
    ui->label_errorMsg7->setText("Invalid Updation Input.");
    ui->label_errorMsg8->setText("Invalid Deletion Input.");
    ui->label_errorMsg9->setText("Invalid Drop Query.");
    ui->label_errorMsg10->setText("Invalid Where Query.");

    ui->label_errorMsg0->hide();
    ui->label_errorMsg1->hide();
    ui->label_errorMsg2->hide();
    ui->label_errorMsg3->hide();
    ui->label_errorMsg4->hide();
    ui->label_errorMsg5->hide();
    ui->label_errorMsg6->hide();
    ui->label_errorMsg7->hide();
    ui->label_errorMsg8->hide();
    ui->label_errorMsg9->hide();
    ui->label_errorMsg10->hide();

    ui->label_errorMsg0->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg1->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg2->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg3->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg4->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg5->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg6->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg7->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg8->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg9->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
    ui->label_errorMsg10->setStyleSheet(
        "QLabel {color: white; font-weight: bold; font-size: 15px}"
    );
}

void DatabaseScreen::paintEvent(QPaintEvent *event)
{
    //backgroundPixmap.load("D:/DS Project/DBMS_finalProject3/DatabaseScreen2.jpg");
    backgroundPixmap.load(":/images/DatabaseScreen.jpg");

    QPainter painter(this);
    painter.setOpacity(0.85);
    painter.drawPixmap(0, 0, backgroundPixmap);

    backgroundPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio);

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    setAutoFillBackground(true);
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
        temp = temp->next;
    }

    if(tableButton != NULL){
        delete[] tableButton;
        tableButton = NULL;
    }

    tableButton = new QPushButton[tableName.count()];

    for(int i=0; i<tableName.count(); i++)
    {
        layout->setVerticalSpacing(10);
        tableButton[i].setParent(ui->frame);
        tableButton[i].setText(tableName[i]);
        layout->addWidget(&tableButton[i], x++, y);
    }

    temp = d1.table_list.head;

    for(int i=0; i<tableName.count(); i++)
    {
        auto data = temp->data;
        connect(&tableButton[i], &QPushButton::clicked, [data, this](){
            displayTable(data);
        });

        temp = temp->next;
    }

    for(int i=0; i<tableName.count(); i++)
    {
        tableButton[i].setStyleSheet(
            "QPushButton {background-color: black; color: white; font-weight: bold; font-size: 25; border: 2px solid black;}"
            "QPushButton:hover {background-color : white; color: black;font-weight: bold; font-size: 25; border: 2px solid black; border-radius: 3px;}"
            );
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

    for(int i = 0; i<queries.size(); i++){
        QStringList textLines = queries.at(i).split("\n");

        Queue<std::string> input;

        for(int i=0; i<textLines.size(); i++){
            input.enQueue(QString(textLines[i]).toStdString());
        }

        vector<string> words = g1.GetWords(input);
        db.processQuery(words);

        if(db.temp_select != NULL){
            createTable(db.temp_select);
            delete db.temp_select;
        }
    }

    if(db.status.at(0) == 1)
    {
        ui->label_errorMsg0->show();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(1) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->show();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(2) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->show();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(3) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->show();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(4) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->show();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(5) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->show();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(6) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->show();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(7) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->show();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(8) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->show();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(9) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->show();
        ui->label_errorMsg10->hide();
    }
    else if(db.status.at(10) == 1)
    {
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->show();
    }
    else{
        ui->label_errorMsg0->hide();
        ui->label_errorMsg1->hide();
        ui->label_errorMsg2->hide();
        ui->label_errorMsg3->hide();
        ui->label_errorMsg4->hide();
        ui->label_errorMsg5->hide();
        ui->label_errorMsg6->hide();
        ui->label_errorMsg7->hide();
        ui->label_errorMsg8->hide();
        ui->label_errorMsg9->hide();
        ui->label_errorMsg10->hide();
    }


    display();

}

void DatabaseScreen::createTable(Table *obj)
{
    ui->tableWidget->setColumnCount(obj->num_of_cols);
    ui->tableWidget->setRowCount(obj->num_of_rows);

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
            item->setTextAlignment(Qt::AlignCenter);
            item->setBackground(QColor(50, 50, 50));
            item->setForeground(QColor(Qt::white));

            ui->tableWidget->setItem(i, j, item);
        }
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->verticalHeader()->hide();


}

void DatabaseScreen::on_pushButton_exit_clicked()
{
    MainScreen *obj = new MainScreen;
    obj->showMaximized();
    obj->show();
    close();
}

