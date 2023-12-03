#ifndef DISPLAYTABLE_H
#define DISPLAYTABLE_H

#include <QDialog>
#include "Table.h"

namespace Ui {
class DisplayTable;
}

class DisplayTable : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayTable(QWidget *parent = nullptr);
    void addTableObject(Table *obj);
    ~DisplayTable();

private:
    Ui::DisplayTable *ui;
};

#endif // DISPLAYTABLE_H
