#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QFile>
#include <QDataStream>

#include "Table.h"
#include "Dependencies.h"
#include "LinkedList.h"

using namespace std;

class Database{

public:
    Database(string name);
    Database(Table& table1, Table& table2);
    string name;
    string username;
    string password;
    int num_of_tables;

    Table* t1;
    Table* t2;
    Table* temp;

    LinkedList<Table*> table_list;

    void pull();
    void join();    //right now, the join is hardcoded. Waiting for SAB's input parser.
    void commit();
    void addTable(Table* table);
    void printTables();
};

#endif // DATABASE_H
