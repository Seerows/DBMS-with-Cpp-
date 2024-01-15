#include "displaytable.h"
#include "ui_displaytable.h"

DisplayTable::DisplayTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayTable)
{
    ui->setupUi(this);
}

void DisplayTable::addTableObject(Table *obj)
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    ui->tableWidget->verticalHeader()->hide();
}

DisplayTable::~DisplayTable()
{
    delete ui;
}
